#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "WheelTimer.h"
#include "LinkedListApi.h"

struct _wheel_timer_elem_{
  int time_interval;
  int execute_cycle_no;
  app_call_back app_callback;
  void *arg;
  int arg_size;
  char is_recurrence;
};

struct _wheel_timer_{
  int current_clock_tic;
  int clock_tic_interval;
  int wheel_size;
  int current_cycle_no;
  pthread_t wheel_thread;
  ll_t *slots[0];
};

static void*
wheel_fn(void *arg){
  wheel_timer_t *wt = (wheel_timer_t*)arg;
  wheel_timer_elem_t *wt_elem = NULL;
  int absolute_slot_num = 0;
  ll_t *slot_list = NULL;
  ll_node *head = NULL, *prev_node = NULL;
  while(1){
    wt->current_clock_tic++;
    if(wt->current_clock_tic == wt->wheel_size){
      wt->current_clock_tic = 0;
      wt->current_cycle_no++;
    }
    sleep(wt->clock_tic_interval);
    slot_list = wt->slots[wt->current_clock_tic];
    absolute_slot_num = GET_WT_CURRENT_ABS_SLOT_NO(wt);
    printf("Wheel Timer Time = %d : ", absolute_slot_num * wt->clock_tic_interval);
    //if(is_ll_empty(slot_list))
      printf("\n");
  }

  ITERATE_LIST_BEGIN_ENHANCED(slot_list, head, prev_node){
    wt_elem = (wheel_timer_elem_t*)head->data;
    if(wt->current_cycle_no == wt_elem->execute_cycle_no){
      wt_elem->app_callback(wt_elem->arg, wt_elem->arg_size);
      if(wt_elem->is_recurrence){
        int next_abs_slot_num  = absolute_slot_num + (wt_elem->time_interval/wt->clock_tic_interval);
  			int next_cycle_no     = next_abs_slot_num / wt->wheel_size;
  			int next_slot_no      = next_abs_slot_num % wt->wheel_size;
  			wt_elem->execute_cycle_no 	 = next_cycle_no;
        if(next_slot_no == wt->current_clock_tic){
          ITERATE_LIST_CONTINUE_ENHANCED(slot_list, head, prev_node);
        }
        ll_remove_node(slot_list, head);
        ll_add_node(wt->slots[next_slot_no], head);
      }
      else{
        free_wheel_timer_element((wheel_timer_elem_t*)head->data);
        ll_delete_node(slot_list, head);
      }
    }
  }ITERATE_LIST_END_ENHANCED(slot_list, head, prev_node);
  return NULL;
}

wheel_timer_t*
init_wheel_timer(int wheel_size, int clock_tic_interval){
  wheel_timer_t *wt = calloc(1, sizeof(wheel_timer_t) + wheel_size*sizeof(ll_t*));
  wt->clock_tic_interval = clock_tic_interval;
  wt->wheel_size = wheel_size;
  wt->current_cycle_no = 0;
  memset(&(wt->wheel_thread), 0, sizeof(wheel_timer_t));
  int i = 0;
  for(; i< wheel_size; i++)
    wt->slots[i] = init_singly_ll();
  return wt;
}

void
start_wheel_timer(wheel_timer_t *wt){
  pthread_t *thread = &wt->wheel_thread;
  if(pthread_create(thread, NULL, wheel_fn, (void*)wt)){
    printf("Wheel timer thread initialization failed, exiting ...\n");
    exit(0);
  }
}

wheel_timer_elem_t*
register_app_event(wheel_timer_t *wt, app_call_back call_back, void *arg, int arg_size, int time_interval, char is_recursive){
    if(!wt || !call_back) return NULL;
    wheel_timer_elem_t *wt_elem = calloc(1, sizeof(wheel_timer_elem_t));
    wt_elem->time_interval = time_interval;
    wt_elem->app_callback = call_back;
    wt_elem->arg = calloc(1, arg_size);
    memcpy(wt_elem->arg, arg, arg_size);
    wt_elem->arg_size = arg_size;
    wt_elem->is_recurrence = is_recursive;

    int wt_absolute_slot = GET_WT_CURRENT_ABS_SLOT_NO(wt);
  	int registration_next_abs_slot = wt_absolute_slot + (wt_elem->time_interval/wt->clock_tic_interval);
  	int cycle_no = registration_next_abs_slot / wt->wheel_size;
  	int slot_no  = registration_next_abs_slot % wt->wheel_size;
  	wt_elem->execute_cycle_no = cycle_no;
    if(add_node_by_val(wt->slots[slot_no], wt_elem) != 0){
      printf("error in adding event to the linked list\n");
      return NULL;
    }
    return wt_elem;
}

void
free_wheel_timer_element(wheel_timer_elem_t *wt_elem){
	free(wt_elem->arg);
	free(wt_elem);
}

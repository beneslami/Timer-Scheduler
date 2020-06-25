#include <stdio.h>
#include <string.h>
#include "WheelTimer.h"
#include "LinkedListApi.h"

void
print_(char *str){
    printf("%s\n", str);
}
void wrapper_print(void *arg, int arg_size){
  char *str = (char*)arg;
  print_(str);
}

int
main(int argc, char **argv){
  wheel_timer_t *wt = init_wheel_timer(5, 1); //10 -> the number of slots , 1->time it takes between each slot
  start_wheel_timer(wt); /* Wheel timer has started running in a separte thread. */

  /* Register the events to be triggered with Wheel timer now. */
  wheel_timer_elem_t *wt_elem = register_app_event(wt, wrapper_print, "ben_event", strlen("ben_event"), 3, 1);

  scanf("\n");
  return 0;
}

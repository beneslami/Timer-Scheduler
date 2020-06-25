#ifndef WHEELTIMER_H
#define WHEELTIMER_H

/*Gives the absolute slot no since the time WT has started*/
#define GET_WT_CURRENT_ABS_SLOT_NO(wt)	((wt->current_cycle_no * wt->wheel_size) + wt->current_clock_tic)

typedef struct _wheel_timer_ wheel_timer_t;           /* opage structure */
typedef struct _wheel_timer_elem_ wheel_timer_elem_t; /* opage structure */
typedef void (*app_call_back)(void *arg, int sizeof_arg);

wheel_timer_t*
init_wheel_timer(int, int);
void
start_wheel_timer(wheel_timer_t*);
wheel_timer_elem_t*
register_app_event(wheel_timer_t*, app_call_back , void*, int ,int , char);
void
de_register_app_event(wheel_timer_elem_t*, wheel_timer_elem_t*);
void
wt_elem_reschedule(wheel_timer_elem_t*, int);
void
free_wheel_timer_element(wheel_timer_elem_t*);
void
print_wheel_timer(wheel_timer_t*);
void
cancel_wheel_timer(wheel_timer_t*);
void
reset_wheel_timer(wheel_timer_t*);
void
free_wheel_timer_element(wheel_timer_elem_t*);

#endif

#include <stdio.h>
#include "WheelTimer.h"
#include "LinkedListApi.h"

int
main(int argc, char **argv){
  wheel_timer_t *wt = init_wheel_timer(/*wheel size, wheel timer clock tic interval -> by Macro  */);
  start_wheel_timer(wt); /* Wheel timer has started running in a separte thread. */

  /* Register the events to be triggered with Wheel timer now. */
  wheel_timer_elem_t *wt_elem = register_app_event(wt,
  /*wrapper function*/, /*input*/, /*input length*/,
  /*period */, 1 /*(infinite)*/);

  scanf("\n");
  return 0;
}

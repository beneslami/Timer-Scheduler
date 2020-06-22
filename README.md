# Timer-Scheduler

It is very common scenario in System Programming, that the application need to perform some action periodically. Hence, there should be a mechanism to systematically fire up or trigger some processing periodically. Among different kinds of data structures, **Wheel Timer** is the one used for this purpose. It gives us the ability to schedule and fire up events periodically. One simple application of Wheel Timer is in control plane domain, where a network protocol needs to send update messages periodically to adjacent nodes.

Look at below picture. There are 10 slots in out Wheel timer. And each slot corresponds to 1 second. So, our Wheel timer resembles to a wall clock, which have 10 seconds in one round instead of 60 seconds.
![picture](data\wheel1.png)

Each slot has some linked list attached to it. This list is a list of events to be triggered when clock tick hits that particular slot. Every time the wheel timer complete one rotation, R is increased by 1.

![picture](data\wheel2.png)

When the pointer of the clock points to let's say slot number 2, All events which are formed in a linked list will be fired up.

There are mainly two design challenges:

1. When an event needs to be executed every let's say 3 seconds. In that case, each time the pointer reaches that event, it needs to re-schedule it in three seconds later from its current time slot.

2. When an event needs to be executed every let's say 30 seconds. In this case, the timer should pass three full rotation. In this situation, the value R will be considered.

Events are nothing but function pointers. 

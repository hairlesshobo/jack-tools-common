#include <errno.h>
#include <time.h>

#include "time-pause.h"
#include "time-timespec.h"

void pause_for(double t)
{
  struct timespec req = double_to_timespec(t);
  struct timespec rem;
  int err = clock_nanosleep(CLOCK_REALTIME,0,&req,&rem);
  if(err == EINTR) {
    clock_nanosleep(CLOCK_REALTIME,0,&rem,NULL);
  }
}

void pause_until(double t)
{
  struct timespec req = double_to_timespec(t);
  int err = clock_nanosleep(CLOCK_REALTIME,TIMER_ABSTIME,&req,NULL);
  if(err == EINTR) {
    pause_until(t);
  }
}

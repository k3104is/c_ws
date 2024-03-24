#include <stdio.h>
#include <time.h>
#include "tm.h"
// #include <sys/time.h>

#define CAL_ELAPSED(end, start) (double)( (double)(end.tv_sec   + (double)end.tv_nsec   * 1e-9) \
                                        - (double)(start.tv_sec + (double)start.tv_nsec * 1e-9))

void Tm_GetElapsedTime(void (*func)(void))
{
  struct timespec start;
  struct timespec end;

  clock_gettime(CLOCK_MONOTONIC, &start);
  func();
  clock_gettime(CLOCK_MONOTONIC, &end);
  
  printf("elapsed:%10.9lf\n", CAL_ELAPSED(end, start));

}
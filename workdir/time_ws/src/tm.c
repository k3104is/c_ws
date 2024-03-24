#include <stdio.h>
#include <time.h>
#include "tm.h"
// #include <sys/time.h>

#define CAL_ELAPSED(end, start) (end.tv_sec - start.tv_sec), (end.tv_nsec - start.tv_nsec)

void Tm_GetElapsedTime(void (*func)(void))
{
  struct timespec start;
  struct timespec end;

  clock_gettime(CLOCK_MONOTONIC, &start);
  func();
  clock_gettime(CLOCK_MONOTONIC, &end);
  
  printf("elapsed:%10ld.%09ld\n", CAL_ELAPSED(end, start));

}
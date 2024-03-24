#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define CAL_ELAPSED(end, start) (end - start)

int main()
{
  struct timespec start;
  struct timespec end;

  clock_gettime(CLOCK_MONOTONIC, &start);
  sleep(1);
  clock_gettime(CLOCK_MONOTONIC, &end);
  
  printf("elapsed:%ld.%09ld\n", (end.tv_sec - start.tv_sec), (end.tv_nsec - start.tv_nsec));
  return 0;
}
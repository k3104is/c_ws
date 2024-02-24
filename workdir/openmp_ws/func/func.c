#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main()
{
  int nhthreads, myid;

  nhthreads = omp_get_max_threads();  /* max thread */
  printf("num of threads:%d\n\n", nhthreads);

#pragma omp parallel for
  for(int i = 0; i < 10; i++)
  {
    myid = omp_get_thread_num();
    printf("hello:%d, thread:%d\n", i, myid);
    sleep(1);
  }

  return 0;
}

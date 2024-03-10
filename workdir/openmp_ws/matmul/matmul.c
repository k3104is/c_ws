#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 500
#define TS_TO_VAL(ts) ((double)ts.tv_sec + (double)(ts.tv_nsec * 1.e-9))


int main()
{
  int A[N][N], B[N][N], C[N][N];
  int i, j, k;
  struct timespec ts;
  double t0, t1, t2;

  /* init */
  clock_gettime(CLOCK_REALTIME, &ts);
  t0 = TS_TO_VAL(ts);
  for(i = 0; i < N; i++)
  {
    for(j = 0; j < N; j++)
    {
      A[i][j] = rand();
      B[i][j] = rand();
    }
  }

  /* calc */
  clock_gettime(CLOCK_REALTIME, &ts);
  t1 = TS_TO_VAL(ts);
#pragma omp parallel for private(i, j, k) shared(C)
  for(i = 0; i < N; i++)
  {
    for(j = 0; j < N; j++)
    {
      C[i][j] = 0;
      for(k = 0; k < N; k++)
      {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  /* end */
  clock_gettime(CLOCK_REALTIME, &ts);
  t2 = TS_TO_VAL(ts);
  printf("init= %f \n", t1 - t0);
  printf("calc= %f \n", t2 - t1);
  printf("total= %f \n", t2 - t0);
  return 0;
}
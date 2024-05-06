#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 512
#define TS_TO_VAL(ts) ((double)ts.tv_sec + (double)(ts.tv_nsec * 1.e-9))
#define RAND_LIMIT 100
#define IBL 16
#define TRIAL_CNT 5

int main()
{
  int A[N][N], B[N][N], C[N][N];
  int da0, da1, db0, db1, dc00, dc01, dc10, dc11;
  int i, j, k, ib, jb, kb, i1, i2, i3, j1, j2, j3;
  int cnt;
  struct timespec ts0, ts1;
  double sum = 0;

  for(cnt = 0; cnt < TRIAL_CNT; cnt++)
  {
  /* init */
  for(i = 0; i < N; i++)
  {
    for(j = 0; j < N; j++)
    {
      A[i][j] = rand() % RAND_LIMIT;
      B[i][j] = rand() % RAND_LIMIT;
      C[i][j] = 0;
    }
  }

  /* calc */
  clock_gettime(CLOCK_REALTIME, &ts0);
#if defined(LOOP_UNROLLING)
  for(i = 0; i < N; i+=4)
  {
    i1 = i + 1;
    i2 = i + 2;
    i3 = i + 3;
    for(j = 0; j < N; j+=4)
    {
      j1 = j + 1;
      j2 = j + 2;
      j3 = j + 3;
      for(k = 0; k < N; k++)
      {
        C[i ][j ] += A[i ][k] * B[k][j ];
        C[i ][j1] += A[i ][k] * B[k][j1];
        C[i ][j2] += A[i ][k] * B[k][j2];
        C[i ][j3] += A[i ][k] * B[k][j3];

        C[i1][j ] += A[i1][k] * B[k][j ];
        C[i1][j1] += A[i1][k] * B[k][j1];
        C[i1][j2] += A[i1][k] * B[k][j2];
        C[i1][j3] += A[i1][k] * B[k][j3];

        C[i2][j ] += A[i2][k] * B[k][j ];
        C[i2][j1] += A[i2][k] * B[k][j1];
        C[i2][j2] += A[i2][k] * B[k][j2];
        C[i2][j3] += A[i2][k] * B[k][j3];

        C[i3][j ] += A[i3][k] * B[k][j ];
        C[i3][j1] += A[i3][k] * B[k][j1];
        C[i3][j2] += A[i3][k] * B[k][j2];
        C[i3][j3] += A[i3][k] * B[k][j3];
      }
    }
  }
#endif  /* defined(LOOP_UNROLLING) */

#if defined(BLOCKING)
  for(ib = 0; ib < N; ib += IBL)
  {
    for(jb = 0; jb < N; jb += IBL)
    {
      for(kb = 0; kb < N; kb += IBL)
      {
        for(i = ib; i < ib + IBL; i++)
        {
          for(j = jb; j < jb + IBL; j++)
          {
            for(k = kb; k < kb + IBL; k++)
            {
              C[i][j] += A[i][k] * B[k][j];
            }
          }
        }
      }
    }
  }
#endif  /* defined(BLOCKING) */


#if defined(LOOP_UNROLLING_AND_BLOCKING)
  for(ib = 0; ib < N; ib += IBL)
  {
    for(jb = 0; jb < N; jb += IBL)
    {
      for(kb = 0; kb < N; kb += IBL)
      {
        for(i = ib; i < ib + IBL; i+=4)
        {
          i1 = i + 1;
          i2 = i + 2;
          i3 = i + 3;
          for(j = jb; j < jb + IBL; j+=4)
          {
            j1 = j + 1;
            j2 = j + 2;
            j3 = j + 3;
            for(k = kb; k < kb + IBL; k++)
            {
              C[i ][j ] += A[i ][k] * B[k][j ];
              C[i ][j1] += A[i ][k] * B[k][j1];
              C[i ][j2] += A[i ][k] * B[k][j2];
              C[i ][j3] += A[i ][k] * B[k][j3];

              C[i1][j ] += A[i1][k] * B[k][j ];
              C[i1][j1] += A[i1][k] * B[k][j1];
              C[i1][j2] += A[i1][k] * B[k][j2];
              C[i1][j3] += A[i1][k] * B[k][j3];

              C[i2][j ] += A[i2][k] * B[k][j ];
              C[i2][j1] += A[i2][k] * B[k][j1];
              C[i2][j2] += A[i2][k] * B[k][j2];
              C[i2][j3] += A[i2][k] * B[k][j3];

              C[i3][j ] += A[i3][k] * B[k][j ];
              C[i3][j1] += A[i3][k] * B[k][j1];
              C[i3][j2] += A[i3][k] * B[k][j2];
              C[i3][j3] += A[i3][k] * B[k][j3];
            }
          }
        }
      }
    }
  }
#endif  /* defined(LOOP_UNROLLING_BLOCKING) */


#if defined(OPENMP) || defined(OPENACC) || defined(NORMAL)
#ifdef OPENMP
#pragma omp parallel for private(i, j, k) shared(C)
#endif
#ifdef OPENACC
#pragma acc data copyin(A, B), copy(C)
#pragma acc kernels
#pragma acc loop
#endif
  for(i = 0; i < N; i++)
  {
    for(j = 0; j < N; j++)
    {
      for(k = 0; k < N; k++)
      {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
#endif  /* defined(OPENMP) || defined(OPENACC) */

  /* end */
  clock_gettime(CLOCK_REALTIME, &ts1);
  sum += TS_TO_VAL(ts1) - TS_TO_VAL(ts0);
  for(i = 0; i < N; i++)
  {
    for(j = 0; j < N; j++)
    {
      if(C[i][j] < 0)
      {
        printf("NG!\n");
        return 1;
      }
    }
  }
  }
  printf("calc\t= %f [s]\n", sum);
  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 512
#define TS_TO_VAL(ts) ((double)ts.tv_sec + (double)(ts.tv_nsec * 1.e-9))
#define RAND_LIMIT 100
#define IBL 16

int main()
{
  int A[N][N], B[N][N], C[N][N];
  int da0, da1, db0, db1, dc00, dc01, dc10, dc11;
  int i, j, k, ib, jb, kb;
  struct timespec ts[3];
  double t[3];

  /* init */
  clock_gettime(CLOCK_REALTIME, &ts[0]);
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
  clock_gettime(CLOCK_REALTIME, &ts[1]);
#if defined(LOOP_UNROLLING)
#if 0
  for(i = 0; i < N; i+=2)
  {
    for(j = 0; j < N; j+=2)
    {
      for(k = 0; k < N; k++)
      {
        C[i  ][j  ] += A[i  ][k] * B[k][j  ];
        C[i  ][j+1] += A[i  ][k] * B[k][j+1];
        C[i+1][j  ] += A[i+1][k] * B[k][j  ];
        C[i+1][j+1] += A[i+1][k] * B[k][j+1];
      }
    }
  }
#else
  // printf("loop_unrolling\n");
  for(i = 0; i < N; i += 2)
  {
    for(j = 0; j < N; j += 2)
    {
      dc00 = C[i  ][j  ];
      dc01 = C[i  ][j+1];
      dc10 = C[i+1][j  ];
      dc11 = C[i+1][j+1];
      for(k = 0; k < N; k++)
      {
        da0 = A[i  ][k  ];
        da1 = A[i+1][k  ];
        db0 = A[k  ][j  ];
        db1 = A[k  ][j+1];

        dc00 += da0 * db0;
        dc01 += da0 * db1;
        dc10 += da1 * db0;
        dc11 += da1 * db1;
      }
      C[i  ][j  ] = dc00;
      C[i  ][j+1] = dc01;
      C[i+1][j  ] = dc10;
      C[i+1][j+1] = dc11;
    }
  }
#endif
#endif  /* defined(LOOP_UNROLLING) */

#if defined(BLOCKING)
  // printf("blocking\n");
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

#if defined(OPENMP) || defined(OPENACC) || defined(NORMAL)
  // printf("normal/openmp\n");
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
  clock_gettime(CLOCK_REALTIME, &ts[2]);
  t[0] = TS_TO_VAL(ts[0]);
  t[1] = TS_TO_VAL(ts[1]);
  t[2] = TS_TO_VAL(ts[2]);
  printf("init\t= %f \n", t[1] - t[0]);
  printf("calc\t= %f \n", t[2] - t[1]);
  printf("total\t= %f \n", t[2] - t[0]);

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
  return 0;
}
#include <stdio.h>

int main()
{
  int i, j;
  int a[9] = {1,2,3,4,5,6,7,8,9};
  int b[9] = {1,2,3,4,5,6,7,8,9};
  int c[9][9] = {0};

#ifdef NG
#pragma omp parallel for
#else
#pragma omp parallel for private(j)
#endif
  for(i = 0; i < 9; i++)
  {
    for(j = 0; j < 9; j++)
    {
      c[i][j] = a[i] * b[j];
    }
  }

  for(i = 0; i < 9; i++)
  {
    for(j = 0; j < 9; j++)
    {
      printf("%d * %d = %d\n", a[i], b[j], c[i][j]);
    }
  }
  return 0;
}

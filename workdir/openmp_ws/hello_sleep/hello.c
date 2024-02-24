#include <stdio.h>
#include <unistd.h>

int main()
{
#pragma omp parallel for
  for(int i = 0; i < 10; i++)
  {
    printf("hello:%d\n", i);
    sleep(1);
  }

  return 0;
}

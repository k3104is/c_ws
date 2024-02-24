#include <stdio.h>

int main()
{
    int i;
    int a[10] = {0};

    a[0] = 10;

    #pragma omp parallel for
    for(i = 1; i < 10; i++)
    {
        a[i] = a[i - 1] + 1;
        printf("a[%d] = %d\n",i, a[i]);
    }
    return 0;
}

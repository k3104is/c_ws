#include <stdio.h>

int main()
{
    int i, j;
    int ddot = 0;
    int a[9] ={1,2,3,4,5,6,7,8,9};
    int b[9] ={1,2,3,4,5,6,7,8,9};


    // #pragma omp parallel for private(j)
    #pragma omp parallel for private(j) reduction(+: ddot)
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            ddot += a[i] * b[j];
        }
    }
    printf("ddot = %d\n", ddot);
    return 0;
}

#include <stdio.h>

int main()
{
    int i, j;
    int a[9] ={1,2,3,4,5,6,7,8,9};
    int b[9] ={1,2,3,4,5,6,7,8,9};

    #pragma omp parallel for
    // #pragma omp parallel for private(j)
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            printf("%d * %d = %d\n", a[i], b[j], (a[i] * b[j]));
        }
    }
    return 0;
}

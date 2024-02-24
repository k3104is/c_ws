#include <stdio.h>

int main()
{
    int i, j;
    int a[9] ={1,2,3,4,5,6,7,8,9};
    int b[9] ={1,2,3,4,5,6,7,8,9};
    int tmp;

    #pragma omp parallel for
    // #pragma omp parallel for private(tmp, j)
    for(i = 0; i < 9; i++)
    {
        tmp = a[i];
        for(j = 0; j < 9; j++)
        {
            printf("%d * %d = %d\n", tmp, b[j], (tmp * b[j]));
        }
    }
    return 0;
}

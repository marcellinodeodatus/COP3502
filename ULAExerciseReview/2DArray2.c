#include <stdio.h>

int main()
{
    int s[4][2] =
        {
            {5, 6},
            {8, 23},
            {22, 9},
            {90, 4}};
    int i, j;
    for (i = 0; i <= 3; i++)
    {
        printf("\n");
        for (j = 0; j <= 1; j++)
            printf("%d ", *(*(s + i) + j));
    }

    return 0;
}
/* Output:
5 6
8 23
22 9
90 4
*/
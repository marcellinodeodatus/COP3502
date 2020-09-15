#include <stdio.h>
#include <stdlib.h>
/*Demo: 2-D Array is an array of arrays*/
int main()
{

    int s[4][2] = {
        {5, 6},
        {8, 23},
        {22, 9},
        {90, 4}};

    int i;
    for (i = 0; i <= 3; i++)
    {
        printf("\nAddress of %d th 1-D array = %u (using s[i])", i, s[i]);
        printf("\nAddress of %d th 1-D array = %u (using *(s+i) )", i, *(s + i));
    }
    return 0;
}
/* output:
Address of 0 th 1-D array = 2961709872
Address of 1 th 1-D array = 2961709880
Address of 2 th 1-D array = 2961709888
Address of 3 th 1-D array = 2961709896*/
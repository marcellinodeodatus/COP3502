#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// big o

int main()
{
    // big oh does not refer to a specific number of values
    // it always uses a high number that is labeled as n

    // big oh of linear search
    // we have an array of 'n' integers long

    // if we have to find the number 5 in that array,
    // what is the big oh of the operation

    // linear search - look at every number one by one to see if it is the 5

    // 1 2 3 4 5 6 7 8 9 10 ..... 100000000

    // big oh- regardless of which case it's always really large

    // worst case- O(n) because it has to go all the way to the end

    // average case- O(n)

    // best case- if the target is at the front of the list O(1)

    // what situation would cause the worst case big O in a linear search?
    // when the target is at the very end

    // in general big Oh of n is pretty slow

    // how can we make a search faster? What is faster that linear search?

    // the binary search is a faster way to find an item
    // before using a binary search the list has to be sorted

    // what is the big oh of a binary search?
    // binary search splits the array in half over and over to find the target
    // usually splitting things in half means the big oh is O(log(n))

    // which is faster O(n) or O(log(n))? O(log(n)) is faster

    // big oh related to linked lists

    // we have a linked list that has a total of n nodes

    // what is the average big oh of finding a node in the list
    // O(n)

    // what is the big oh of the best case of finding a node in the list
    // O(1)

    // what is the big oh of adding an item to the back of the list
    // O(n + 1) -----> O(n)

    // what is the big oh of removing the head?
    // O(3) ----> O(1)

    // you should know the big oh of any important functions
    // binary Search - O(log(n))  split in half over and over
    // linear search - O(n)
    // ternary search - O(log(n))  split into 3 over and over
    int n = 5;
    // sorting algorithms
    int x = 0;

    // O(n)
    for (int i = 0; i < n; i++)
        x++;

    // O(n^2)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                x++;
    printf("%d\n", x);
    // each nested for loop makes it one more square
    // O(n^3)

    // what is the big oh of the entire program
    // O(n^2)

    return 0;
}
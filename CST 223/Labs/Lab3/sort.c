/*****************************************************************************
* File:		sort.c
* Author:	Logan Wright
* Purpose:	Sorts four integers and prints result to console
*****************************************************************************/

#include <stdio.h>

// Dont use any other C- language function such as qsort
void PrintInOrder(int X1, int X2, int X3, int X4)
{
    int Y1, Y2, Y3, Y4;

    // sort numbers using array cell swaps
    int done, idx[] = { X1, X2, X3, X4 };
    do {
        done = 1;
        int i;
        for (i = 1; i < 4; i++)
        {
            if (idx[i] < idx[i - 1])
            {
                int val = idx[i];
                idx[i] = idx[i - 1];
                idx[i - 1] = val;
                done = 0;
            }
        }
    } while (!done);

    // populate given variables
    Y1 = idx[0];
    Y2 = idx[1];
    Y3 = idx[2];
    Y4 = idx[3];

    printf("\nThe smallest number is %d", Y1);
    printf("\nThe second smallest number is %d", Y2);
    printf("\nThe third smallest number is %d", Y3);
    printf("\nThe largest number is %d", Y4);
}

int main()
{
    PrintInOrder(2, 1, 5, 10);
    // should print 1, 2, 5 and 10
    
    return 0;
}

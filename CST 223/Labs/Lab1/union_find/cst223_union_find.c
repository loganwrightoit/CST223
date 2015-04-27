/*****************************************************************************
* File:		cst223_union_find.c
* Author:	Logan Wright
* Purpose:	Performs union-find operations on sets verified using asserts.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_SETS 10

struct node
{
    struct node* parent;
    int element;
} typedef node;

node nodeSet[NUM_SETS];

int Find(int num)
{
    node result = nodeSet[num];
    while (result.parent != NULL)
    {
        result = *(result.parent);
    }

    return result.element;
}

void Union(int num1, int num2)
{
    nodeSet[num1].parent = &nodeSet[num2];
}

int main()
{
    // Create sets and store parent pointers in array
    int i;
    for (i = 0; i < NUM_SETS; ++i)
    {
        nodeSet[i].element = i;
    }

    printf("Running tests...\n");

    assert(Find(5) == 5);
    assert(Find(6) != 5);
    Union(5, 1);
    assert(Find(5) == 1);
    assert(Find(1) != 5);
    assert(Find(1) == 1);
    Union(1, 2);
    assert(Find(1) == 2);
    assert(Find(5) == 2);

    printf("All tests complete\n");

    return 0;
}

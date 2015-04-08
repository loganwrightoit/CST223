/*
CST 223 - Concepts of Programming Languages
Lab - Union
Logan Wright

Purpose:  Performs union operations on arrays.
*/

#include <stdio.h>
#include <stdlib.h> // qsort & bsearch

#define MAX_ARRAY_SIZE 10

int compare(const void * a, const void * b, bool ascending)
{
	if (ascending)
	{
		return (*(int*)a - *(int*)b);
	}
	else
	{
		return (*(int*)b - *(int*)a);
	}
}

int find(int num)
{
	// Find first array index containing num
	// Needs some type of BST search stuff

}

// Pushes all non-zero values to beginning of array
void offsetLeft(int array[])
{
	int num = sizeof(array) / sizeof(array[0]); // Number of elements
    int left = 0; // New index for left-shift
 
	// Shift non-zero elements left
	int i;
    for (i = 0; i < num; i++)
	{
        if (array[i] != 0)
		{
            array[left++] = array[i];
		}
	}
 
	// Clear remainder of array
    memset(array + sizeof(array[0]) * left, 0, sizeof(array[0]) * (num - left));
}

void doUnion(int* a_arr, int a_numElem, int* b_arr, int b_numElem)
{
	// Create temp array for union
	int newArray[MAX_ARRAY_SIZE];
	memset(array, 0, sizeof(newArray));
	
	// Copy array to temp
	memcpy(newArray, a_arr, sizeof(a_arr));

	// Do union
	int i, offset = a_numElem;	
	for (i = 0; i < b_numElem; ++i)
	{
		int key = b_arr[i];
		int* ptr_item = (int*) bsearch(&key, b_arr, b_numElem, sizeof(int), compare(true));
		if (ptr_item == NULL)
		{
			// Add element to new array
			newArray[offset] = b_arr[i];
			++offset;
		}
	}
	
	// Copy union result back to 'a' array
	memcpy(a_arr, newArray, MAX_ARRAY_SIZE * sizeof(int));
}

int main()
{
	// Create and initialize array
	int array[10][MAX_ARRAY_SIZE];
	memset(array, 0, sizeof(array));
	int i;
	for (i = 0; i < 10; ++i)
	{
		array[i][0] = i + 1;
	}
	
	// Perform some unions
	
	
	// Find data using binary search
	
	return 0;
}

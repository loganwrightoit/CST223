/*****************************************************************************
* File:		cst223_bst.c
* Author:	Logan Wright
* Purpose:	A binary search tree implementation that saves numbers from a file
*			into a data structure.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h> // qsort & bsearch

struct tree
{
    int value;
    struct tree* left;
    struct tree* right;
};
typedef struct tree node;

int compare(const void * a, const void * b)
{
    return (*(int*)a - *(int*)b);
}

int getNumInts(FILE* file)
{
    int count = 0;
    int i;
    if (fscanf(file, "%d", &i))
    {
        while (!feof(file))
        {
            if (!fscanf(file, "%d", &i))
            {
                break;
            }
            count++;
        }
    }
    rewind(file);

    return count;
}

void treeInsert(node** tree, int num)
{
    node* temp = NULL;
    if (!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->value = num;
        *tree = temp;
        return;
    }

    if (num < (*tree)->value)
    {
        treeInsert(&(*tree)->left, num);
    }
    else if (num > (*tree)->value)
    {
        treeInsert(&(*tree)->right, num);
    }
}

void treeClear(node* tree)
{
    if (tree)
    {
        treeClear(tree->left);
        treeClear(tree->right);
        free(tree);
    }
}

node* treeSearch(node** tree, int num)
{
    if (!(*tree)) // No node here, nothing found
    {
        return NULL;
    }

    if (num < (*tree)->value) // Search left branch
    {
        return treeSearch(&((*tree)->left), num);
    }
    else if (num > (*tree)->value) // Search right branch
    {
        return treeSearch(&((*tree)->right), num);
    }
	else // Found num, return
	{
		return *tree;
	}
}

int main()
{
    // Create tree object
    node* tree = NULL;

	printf("Opening file for reading\n");
	
    // Open input file
    FILE *ptr_file;
    if (!(ptr_file = fopen("numbers.txt", "r")))
    {
        printf("Unable to open file numbers.txt, exiting\n");
        return 1;
    }

    // Get line count
    int numInts = getNumInts(ptr_file);

    // Check numbers exist
    if (numInts <= 0)
    {
        printf("Did not find any values in file, exiting.\n");
        fclose(ptr_file);
        return 1;
    }

	printf("Reading numbers from file\n");
	
    int i;
    for (i = 0; i < numInts; i++)
    {
        // Grab next number
        int num;
        if (!fscanf(ptr_file, "%d", &num))
        {
            printf("Problem reading input file, exiting\n");
            fclose(ptr_file);
			
			if (tree)
			{
				treeClear(tree);
			}
            return 1;
        }

        // Insert number into tree
        treeInsert(&tree, num);
    }

    printf("Loaded %d numbers from file\n", numInts);

    // Close input file
    fclose(ptr_file);

    while (1)
    {
		int num;
        printf("Search for a number (or 0 to quit): ");
        if (!scanf("%d", &num))
        {
            printf("\tNumber entered is invalid\n");
			break;
        }
        else
        {
            if (num == 0)
            {
                break;
            }
            else
            {
                node* result = treeSearch(&tree, num);
                if (result)
                {
                    printf("\tNumber found in tree at node memory %p\n", result);
                }
                else
                {
                    printf("\tNumber not found in tree\n");
                }
            }
        }
    }

    printf("Exiting...\n");
    treeClear(tree);

    return 0;
}

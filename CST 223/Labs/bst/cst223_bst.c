/*****************************************************************************
* File:		cst223_bst.c
* Author:	Logan Wright
* Purpose:	A binary search tree implementation that saves numbers from a file
*			into a data structure.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct tree
{
    int value;
    struct tree* left;
    struct tree* right;
};
typedef struct tree node;

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
	else if (num < (*tree)->value) // Search left branch
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

	printf("Inserting numbers into tree\n");
	
	int count = 0, min, max, num;
    if (fscanf(ptr_file, "%d", &num))
    {
		min = max = num;
        while (!feof(ptr_file))
        {
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

			if (num < min)
			{
				min = num;
			}
			else if (num > max)
			{
				max = num;
			}
	
	        // Insert number into tree
			treeInsert(&tree, num);
	
            count++;
        }
    }
	else
	{
		printf("Problem reading input file, exiting\n");
		fclose(ptr_file);
		
		if (tree)
		{
			treeClear(tree);
		}
		return 1;
	}

    printf("Loaded %d numbers from file (Range %d-%d)\n", count, min, max);

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

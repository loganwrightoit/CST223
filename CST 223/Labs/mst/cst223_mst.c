/*****************************************************************************
* File:		cst223_mst.c
* Author:	Logan Wright
* Purpose:	Performs union-find operations and Kruskal's algorithm to
*			construct a minimum spanning tree.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct node
{
	struct node* parent;
	int element;
} typedef node;

struct edge
{
	struct node* from;
	struct node* to;
	int weight;
} typedef edge;

int compare(const void * x, const void * y)
{
	return (*(edge *)x).weight - (*(edge *)y).weight;
}

node nodeSet[10];
edge edgeSet[10];

int Find(int num)
{
	node result = nodeSet[num];
	while (result.parent != NULL)
	{
		result = *(result.parent);
	}

	return result.element;
}

bool Union(int num1, int num2)
{
	if (num1 != num2)
	{
		nodeSet[num1].parent = &nodeSet[num2];
		return true;
	}
	else
	{
		return false;
	}
}

void Kruskal(int numNodes)
{
	int totalEdges = 0, edgePos = 0, weight;
	edge edgy;
	while (totalEdges < (numNodes - 1))
	{
		edgy = edgeSet[edgePos++];

		// Do a union if parents do not match (build the tree)
		int parent1 = Find(edgy.from->element);
		int parent2 = Find(edgy.to->element);
		if (Union(parent1, parent2))
		{
			totalEdges++;
		}
	}
}

int main()
{
	// Open input file
	FILE *ptr_file;
	if (!(ptr_file = fopen("numbers.txt", "r")))
	{
		printf("Unable to open file numbers.txt, exiting\n");
		return 1;
	}

	int p1, p2, wt, numNodes, numEdges;
	if (fscanf(ptr_file, "%d%d", &numNodes, &numEdges))
	{
		// Initialize node elements
		int i;
		for (i = 0; i < numNodes; ++i)
		{
			nodeSet[i].element = i;
		}

		int counter = 0;
		while (!feof(ptr_file))
		{
			if (!fscanf(ptr_file, "%d%d%d", &p1, &p2, &wt))
			{
				printf("Problem reading input file, exiting\n");
				fclose(ptr_file);
				return 1;
			}
			else
			{
				// Populate edge params
				edgeSet[counter].from = &nodeSet[p1];
				edgeSet[counter].to = &nodeSet[p2];
				edgeSet[counter].weight = wt;
			}
			++counter;
		}
	}
	else
	{
		printf("Problem reading input file, exiting\n");
		fclose(ptr_file);
		return 1;
	}

	printf("Scanned in %d nodes and %d edges\n\n", numNodes, numEdges);

	// Sort edges by weight
	qsort(edgeSet, numEdges, sizeof(edge), compare);

	printf("Sorted edges\n");

	int j;
	for (j = 0; j < numEdges; j++)
	{
		printf("Edge %d has pair(%d,%d) and weight of %d\n", j, edgeSet[j].from->element, edgeSet[j].to->element, edgeSet[j].weight);
	}
	printf("\n");

	// Run Kruskal algorithm
	Kruskal(numNodes);

	printf("Minimum spanning tree constructed\n");

	printf("Node connections:\n");

	// Print node->parent list
	int i;
	for (i = 0; i < numNodes; i++)
	{
		if (nodeSet[i].parent)
		{
			printf("Node %d connects to %d\n", i, nodeSet[i].parent->element);
		}
		else
		{
			printf("Node %d is the root of the tree\n", i);
		}
	}

	return 0;
}
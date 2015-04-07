/*
CST 223 - Concepts of Programming Languages
Lab1 - Part c
Logan Wright

Purpose:  A binary search tree implementation that reads
	      data from an input file.
*/

#include <stdio.h>
#include <stdlib.h> // qsort & bsearch

int compare (const void * a, const void * b)
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

int main()
{
	// Open input file
	FILE *ptr_file;
	if (!(ptr_file = fopen("numbers.txt", "r")))
	{
		printf("Unable to open file numbers.txt, exiting.\n");
		return 1;
	}
	
	// Get line count
	int numInts = getNumInts(ptr_file);
	
	// Read values from file into array
	if (numInts <= 0)
	{
		printf("Did not find any values in file, exiting.\n");
		fclose(ptr_file);
		return 1;
	}
		
	int* array = malloc(numInts * sizeof(int));
	int i;
	for (i = 0; i < numInts; i++)
	{
		if (!fscanf(ptr_file, "%d", &array[i]))
		{
			printf("Unable to scan during array creation, exiting.\n");
			fclose(ptr_file);
			free(array);
			return 1;
		}
	}
	
	// Close input file
	fclose(ptr_file);
	
	// Sort array
	qsort(array, numInts, sizeof(int), compare);
	
	// Open output file
	FILE *ptr_outfile;
	if (!(ptr_outfile = fopen("sorted.txt", "w")))
	{
		printf("Unable to open output file sorted.txt, exiting.\n");
		free(array);
		return 1;
	}

	// Write sorted numbers to file
	int j;
	for (j = 0; j < numInts; j++)
	{
		fprintf(ptr_outfile, "%d\n", array[j]);
	}
	fclose(ptr_outfile);
	free(array);
	
	return 0;
}

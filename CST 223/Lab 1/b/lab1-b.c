/*
CST 223 - Concepts of Programming Languages
Lab1 - Part b
Logan Wright

Purpose:  Computes Fibonacci sequence and factorial of user inputted value.
*/

#include <stdio.h>

int main()
{
	int num = 0;
 
	while (num <= 0)
	{
		printf("Please enter a number greater than zero: ");
		if (!scanf("%d", &num))
		{
			printf("You must enter a valid number.\n");
		}
	}

	printf("Fibonacci sequence: ");

	// Compute Fibonacci sequence
	if (num == 1)
	{
		printf("0");
	}
	else
	{
		printf("0, 1");
		int i, newNum = num - 2, tmp2 = 1, tmp1 = 0, tmp0 = 0;
		for (i = 0; i < newNum; i++)
		{
			tmp0 = tmp1;
			tmp1 = tmp2;
			tmp2 = tmp0 + tmp1;
			printf(", %d", tmp2);
		}
	}
	printf("\n");
	
	// Compute factorial
	int j, fact = 1;
	for (j = 1; j <= num; j++)
	{
		fact *= j;
	}
	
	printf("Factorial: %d\n", fact);

	return 0;
}

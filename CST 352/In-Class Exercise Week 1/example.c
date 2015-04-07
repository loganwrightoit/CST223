/* File: example.c
   This program asks the user for his/her name and two numbers.
   It computes and displays the sum, difference, product,
   quotient and remainder of the two numbers.
*/

#include <stdio.h>   /* scanf, printf */

#define MAX_NAME_SIZE 20

int main ()
{
   int num1, num2, result;
   char name[MAX_NAME_SIZE];

   printf ("\nPlease tell me your first name: ");
   scanf ("%s", name);
   printf ("\nHello, %s\n\n", name);
   printf ("Please enter two integers, separated by spaces: ");
   scanf ("%d %d", &num1, &num2);
   printf ("\nYour numbers are: %d and %d\n", num1, num2);

   /* Addition */
   result = num1 + num2;
   printf ("The sum of your numbers is: %d\n", result);

   /* Subtraction */
   result = num1 - num2;
   printf ("The difference of your numbers is: %d\n", result);

   /* Multipication */
   result = num1 * num2;
   printf ("The product of your numbers is: %d\n", result);

   /* Division */
   if (num2 != 0)   /* cannot divide by zero */
   {
      result = num1 / num2;
      printf ("The quotient of your numbers is: %d\n", result);
      result = num1 % num2;
      printf ("The remainder of your numbers is: %d\n", result);
   }
   else
   {
      printf ("Division by zero is not defined\n");
   }

   return 0;
}

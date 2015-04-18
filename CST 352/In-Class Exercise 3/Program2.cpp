#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
	cout << "Ha! ";
	fork();
	cout << "Ho! ";
	fork();
	cout << "He! " << endl;
}
#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
	cout << "Ha! " << endl;
	fork();
	cout << "Ho! " << endl;
	fork();
	cout << "He! " << endl;
}
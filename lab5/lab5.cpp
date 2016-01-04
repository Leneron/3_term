//Matrix on the base of tree
#include <iostream>
#include "array.h"

int main()
{
	//Length of the rows is the length of the longest row
	//Amount of rows will be as many as you set in the initialization
	Array<int> array = { 
		{ 1, 3, 4}, 
		{ 2 }, 
		{ 4, 0 },
		{ 3, 5, 0, 2}
	};

	//Example of using
	cout << array.getElement(0, 2) << endl;
	cout << array[0][2] << endl;
	array[0][2] = 3;
	cout << array[0][2] << endl;
	return 0;
}


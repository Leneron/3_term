//Parallel gaussian elimination

#include <fstream>
#include "Matrix.h"

using namespace std;

int main()
{
	ifstream inputFile;
	inputFile.open("in.txt");
	//Reading the data from input file
	Matrix* matrix = new Matrix(inputFile);
	inputFile.close();
	matrix->solveEquations();

	ofstream outputFile;
	outputFile.open("out.txt");
	//Printing the result
	matrix->printResult(outputFile);
	outputFile.close();
	cout << "done";
	return 0;
}


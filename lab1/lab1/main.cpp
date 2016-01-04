//Gaussian elimination for solving systems of linear equations

#include <fstream>
#include "matrix.h"

using namespace std;

int main()
{
    ifstream inputFile;
    inputFile.open("in.txt");

    //Creating the object with data from file
    Matrix* matrix = new Matrix(inputFile);
    inputFile.close();
    matrix->solveEquations();

    ofstream outputFile;
    outputFile.open("out.txt");

    //Writing the result in the output file
    matrix->printResult(outputFile);
    outputFile.close();
    matrix->~Matrix();
    return 0;
}


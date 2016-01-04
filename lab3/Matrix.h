#pragma once

#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <iostream>
#include <thread>

using namespace std;

class Matrix
{
public:
	Matrix(ifstream& stream);
	virtual ~Matrix();
	void solveEquations();
	void printResult(ofstream& stream);
	void threadFunction(int firstNonZeroI, int i, int t);
private:
	const double UNDEFINED = 1.7e308;
	const double EPSILON = 1.0e-14;
	int numberOfVariables;
	vector<vector<double> > coefficients;
	vector<double> result;
	int numberOfThreads;

	//Works only for independent consistent system
	
	bool isEmpty();
	bool isConsistent();
	bool isIndependent();
	bool isZeroRow(int rowIndex);

	int findFirstNonZero(int rowIndex);
	//Finds the row with the maximum non-zero element from the left
	//Provides better numerical stability
	int pivotingRow(const int &rowIndex);

	void solveIndependentSystem();
	//Essential steps of the Gaussian elimination algorithm
	void forwardPhase();
	void backPhase();
};

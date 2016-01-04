#include "Matrix.h"

Matrix::Matrix(ifstream& stream)
{
	//Reading the data from file
	stream >> numberOfVariables;
	for (int i = 0; i < numberOfVariables; i++)
	{
		vector<double> row;
		for (int j = 0; j < numberOfVariables + 1; j++)
		{
			int coefficient;
			stream >> coefficient;
			row.push_back(coefficient);
		}
		coefficients.push_back(row);
	}
	cout << "Write the number of threads:";
	cin >> numberOfThreads;
}

Matrix::~Matrix()
{

}

void Matrix::solveEquations()
{
	forwardPhase();
	backPhase();
}

void Matrix::printResult(ofstream& stream)
{
	if (!isEmpty())
	{
		if (isConsistent())
		{
			if (isIndependent())
			{
				for (size_t i = 0; i < result.size(); i++)
				{
					stream << "x" << i << " = " << fixed << result[i] << endl;       // Will be printed in this way: "x1 = 23"
				}
			}
			else
			{
				stream << "System is dependent" << endl;
			}
		}
		else
		{
			stream << "System is not consistent" << endl;
		}
	}
	else
	{
		stream << "Empty system" << endl;
	}
}

void Matrix::threadFunction(int firstNonZeroI, int i, int t)
{
	cout << i << " " << t << endl;
	//t is a number of threads
	//blockSize -- the number of rows that 1 thread can calculate
	int blockSize = (coefficients.size() - i - 1) / numberOfThreads + 1;
	for (size_t j = i + 1; (j < coefficients.size()) && (j <= (j + blockSize)); j++)
	{
		int firstNonZeroJ = findFirstNonZero(j);
		if (firstNonZeroI == firstNonZeroJ)
		{
			double factor = coefficients[j][firstNonZeroI] / coefficients[i][firstNonZeroI];
			if (abs(factor) != INFINITY)
				for (int k = firstNonZeroI; k < numberOfVariables + 1; k++)
				{
					coefficients[j][k] = coefficients[j][k] - coefficients[i][k] * factor;
					if (abs(coefficients[j][k]) < EPSILON)
					{
						coefficients[j][k] = 0;
					}
				}
		}
	}
}

bool Matrix::isEmpty()
{
	if (coefficients.size() == 0)
	{
		return true;
	}
	return false;
}

bool Matrix::isConsistent()
{
	const int lastRowIndex = coefficients.size() - 1;
	const int lastColumnIndex = numberOfVariables - 1;
	bool isZero = true;

	for (int i = 0; i <= lastColumnIndex; i++)       //Check the zero row for not augmented matrix
	{
		if (coefficients[lastRowIndex][i] != 0)
		{
			isZero = false;
			return true;
		}
	}
	if (isZero && (coefficients[lastRowIndex][lastColumnIndex + 1] != 0))
	{
		return false;
	}

	return true;
}

bool Matrix::isIndependent()
{
	return ((size_t)numberOfVariables == coefficients.size());
}

bool Matrix::isZeroRow(int rowIndex)
{
	for (int i = 0; i < numberOfVariables + 1; i++)
	{
		if (coefficients[rowIndex][i] != 0)
		{
			return false;
		}
	}

	return true;
}

int Matrix::findFirstNonZero(int rowIndex)
{
	int i = 0;
	while ((i < numberOfVariables) && (coefficients[rowIndex][i] == 0))
	{
		i++;
	}
	return i;
}

int Matrix::pivotingRow(const int& rowIndex)
{
	int pivotingRow = rowIndex;
	for (size_t i = rowIndex + 1; i < coefficients.size(); i++)
	{
		if (coefficients[i][rowIndex] > coefficients[pivotingRow][rowIndex])
		{
			pivotingRow = i;
		}
	}

	return pivotingRow;
}

void Matrix::solveIndependentSystem()
{
	const int lastColumnIndex = numberOfVariables - 1;
	for (int i = coefficients.size() - 1; i >= 0; i--)
	{
		double calculatedVariable = coefficients[i][lastColumnIndex + 1];
		for (int j = lastColumnIndex; j > i; j--)     //Calculating from the last element of the last row
		{
			calculatedVariable = calculatedVariable - result[j] * coefficients[i][j];
		}
		calculatedVariable = calculatedVariable / coefficients[i][i];
		result[i] = calculatedVariable;
	}
}

void Matrix::forwardPhase()
{	
	for (size_t i = 0; i < coefficients.size(); i++)
	{
		vector<thread*> threads;
		int pivotingIndex = pivotingRow(i);

		swap(coefficients[i], coefficients[pivotingIndex]);

		int firstNonZeroI = findFirstNonZero(i);
		if (firstNonZeroI < numberOfVariables)
		{
			for (int t = 1; t <= numberOfThreads; t++)
			{
				//Multithreading
				//Each of the threads with numero tcounts few rows below the current pivoting row
				//Threads divide rows under the pivoting row in equal proportion
				threads.push_back(new thread([&]{threadFunction(firstNonZeroI, i, t); }));
				cout << "threads: " << t << endl;
			}
		}		

		for (int i = 0; i < numberOfThreads; i++)
		{
			threads[i]->join();
			delete threads[i];
		}
	}
	int i = (int)coefficients.size() - 1;
	while (i >= 0)
	{
		if (isZeroRow(i))
		{
			coefficients.erase(coefficients.begin() + i);
		}
		i--;
	}
}

void Matrix::backPhase()
{
	result.resize(numberOfVariables, UNDEFINED);
	if (!isEmpty())
	{
		if (isConsistent())
		{
			if (isIndependent())
			{
				solveIndependentSystem();
			}
		}
	}
}

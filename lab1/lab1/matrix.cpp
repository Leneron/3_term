#include "matrix.h"

Matrix::Matrix(ifstream& stream)
{
    //Reading the data from the file
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
                    // Will be printed in this way: "x1 = 23"
                    stream << "x" << i << " = " << fixed << result[i] << endl;
                }
            }
            else
            {
                for (int i = 0; i < numberOfVariables; i++)
                {
                    stream << "x" << i << " = ";
                    if (!isHomogeneous())
                    {
                        stream << result[i] << " ";
                        if (fundamentalSolution.size())
                        {
                            stream << "+ ";
                        }
                    }
                    for (size_t j = 0; j < fundamentalSolution.size(); j++)
                    {
                        // Will be printed in this way: "x1 = 2*C1 + 4*C2"
                        stream << fixed << fundamentalSolution[j][i] << "*C" << j;
                        (j < fundamentalSolution.size() - 1) ? stream << " + " : stream << endl;
                    }

                }
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

bool Matrix::isHomogeneous()
{
    for (size_t i = 0; i < coefficients.size(); i++)
    {
        if (coefficients[i][numberOfVariables] != 0)
        {
            return false;
        }
    }

    return true;
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
    //Searching the row with the maximum non-zero element from the left
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
    //For every row in the matrix
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

void Matrix::findParticularSolution(bool fundamental)
{
    const int lastColumnIndex = numberOfVariables - 1;
    for (int i = coefficients.size() - 1; i >= 0; i--)
    {
        int firstNonZero = findFirstNonZero(i);

        double calculatedVariable;
        if (fundamental)
        {
            calculatedVariable = 0;
        }
        else
        {
            result.assign(result.size(), 1);      //Define the independent variables
            calculatedVariable = coefficients[i][lastColumnIndex + 1];
        }
        int j = lastColumnIndex;
        for (; j > firstNonZero; j--)     //Calculating from the last element of the last row
        {
            calculatedVariable = calculatedVariable - result[j] * coefficients[i][j];
        }
        calculatedVariable = calculatedVariable / coefficients[i][j];
        result[firstNonZero] = calculatedVariable;
    }
}

void Matrix::findIndependentVariables()
{
    int j = 0;
    for (size_t i = 0; i < coefficients.size(); i++)
    {
        while ((j < numberOfVariables) && ((coefficients[i][j] == 0)))
        {
            independentVariables.push_back(j);
            j++;
        }
        j++;
    }
    while (j < numberOfVariables)
    {
        independentVariables.push_back(j);
        j++;
    }
}

void Matrix::solveIndependentHomogeneousSystem()
{
    for (size_t i = 0; i < independentVariables.size(); i++)       //Define the independent variables
    {
        for (size_t j = 0; j < fundamentalSolution.size(); j++)
        {
            int variableNo = independentVariables[i];
            (j == i) ? fundamentalSolution[j][variableNo] = 1 : fundamentalSolution[j][variableNo] = 0;
        }
    }

    for (size_t i = 0; i < fundamentalSolution.size(); i++)     //Solving the fundamental system
    {
        result = fundamentalSolution[i];
        findParticularSolution();
        fundamentalSolution[i] = result;
    }
}

void Matrix::solveDependentSystem()
{
    findIndependentVariables();
    if (!isHomogeneous())
    {
        findParticularSolution(false);
    }
    vector<double> particularSolution = result;
    solveIndependentHomogeneousSystem();
    result = particularSolution;
}

void Matrix::forwardPhase()
{
    for (size_t i = 0; i < coefficients.size(); i++)
    {
        int pivotingIndex = pivotingRow(i);

        swap(coefficients[i], coefficients[pivotingIndex]);

        int firstNonZeroI = findFirstNonZero(i);
        if (firstNonZeroI < numberOfVariables)
        {
            for (size_t j = i + 1; j < coefficients.size(); j++)
            {
                int firstNonZeroJ = findFirstNonZero(j);
                if (firstNonZeroI == firstNonZeroJ)
                {
                    double factor = coefficients[j][firstNonZeroI] / coefficients[i][firstNonZeroI];
                    if (abs(factor) != INFINITY)
                        for (int k = firstNonZeroI; k < numberOfVariables + 1; k++)
                        {
                            coefficients[j][k] =  coefficients[j][k] - coefficients[i][k] * factor;
                            if (abs(coefficients[j][k]) < EPSILON)
                            {
                                coefficients[j][k] = 0;
                            }
                        }
                }
            }
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
            else
            {
                int numberOfIndependentVariables = numberOfVariables - coefficients.size();
                fundamentalSolution.resize(numberOfIndependentVariables, result);
                solveDependentSystem();
            }
        }
    }
}

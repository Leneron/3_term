#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class Matrix
{
    public:
        Matrix (ifstream& stream);
        virtual ~Matrix();
        void solveEquations();
        void printResult (ofstream& stream);
    private:
        const double UNDEFINED = 1.7e308;
        const double EPSILON = 1.0e-14;
        int numberOfVariables;
        vector<vector<double> > coefficients;
        vector<int> independentVariables;
        vector<double> result;
        vector<vector<double> > fundamentalSolution;

        //This class solves different types of systems
        //including dependent, independent, homogeneous
        //and inform user if the system is inconsistent

        bool isEmpty();
        bool isConsistent();
        bool isIndependent();
        bool isHomogeneous();
        bool isZeroRow (int rowIndex);

        int findFirstNonZero(int rowIndex);

        //Finds the row with the maximum non-zero element from the left
        //Provides better numerical stability
        int pivotingRow (const int &rowIndex);

        void solveIndependentSystem();
        void findParticularSolution(bool fundamental = true);
        void findIndependentVariables();
        void solveIndependentHomogeneousSystem();
        void solveDependentSystem();
        //Essential steps of the Gaussian elimination algorithm
        void forwardPhase();
        void backPhase();
};

#endif // MATRIX_H

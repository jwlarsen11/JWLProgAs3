/*
	Jacob Larsen
	Part 1
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

void printMatrix(vector<vector<double>>& matrix);
void GJE(vector<vector<double>>& matrix);

int main()
{
    ifstream myfile;
    myfile.open("input.txt");
    vector<vector<double>> matrixD(3, vector<double>(3));
    vector<double> matrixE(3, 1);
    vector<vector<double>> interim(3, vector<double>(3));
    vector<double> result(3, 1);
    vector<vector<double>> identity = { {1, 0, 0},
                                        {0, 1, 0},
                                        {0, 0, 1} };
    
    //for in-out matrix D
    cout << "Matrix D: \n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            myfile >> matrixD[i][j];
            cout << matrixD[i][j] << " ";
        }
        cout << endl;
    }

    //for demand matrix E
    cout << "\nMatrix E: \n";
    for (int i = 0; i < 3; i++)
    {
        myfile >> matrixE[i];
        cout << matrixE[i] << "\n";
    }

    //for calculation matrix
    cout << "\nCalculation Matrix: \n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            interim[i][j] = identity[i][j] - matrixD[i][j];
            cout << interim[i][j] << " ";
        }
        cout << endl;
    }

    //calculating with gaus-jordan elimination
    cout << "\nCalculation Matrix after GJE: \n";
    GJE(interim);
    printMatrix(interim);

    //for the output matrix
    cout << "Output Matrix: \n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result[i] += interim[i][j] * matrixE[j];
        }
        result[i] -= 1;
        cout << result[i] << endl;
    }
}


//prints a matrix
void printMatrix(vector<vector<double>>& matrix)
{
    for (const auto& row : matrix)
    {
        for (const auto& elem : row)
            cout << elem << " ";
        cout << endl;
    }
    cout << endl;
}


//gaus-jordan elimination to find the inverse of a matrix
void GJE(vector<vector<double>>& matrix)
{
    const size_t rowCount = matrix.size();
    const size_t columnCount = matrix[0].size();

    // Augment the matrix with the identity matrix
    vector<vector<double>> augmentedMatrix(rowCount, vector<double>(2 * columnCount, 0.0));
    for (size_t i = 0; i < rowCount; ++i) 
    {
        for (size_t j = 0; j < columnCount; ++j) 
        {
            augmentedMatrix[i][j] = matrix[i][j];
            if (i == j) 
            {
                augmentedMatrix[i][j + columnCount] = 1.0;
            }
        }
    }

    for (size_t r = 0; r < rowCount; ++r) {
        // Find the pivot (non-zero entry) in the current column
        size_t lead = r;
        while (augmentedMatrix[lead][r] == 0) 
        {
            ++lead;
            if (lead == rowCount) 
            {
                cerr << "Matrix is not invertible!" << endl;
                return;
            }
        }

        // Normalize the pivot row
        double pivot = augmentedMatrix[lead][r];
        for (size_t j = 0; j < 2 * columnCount; ++j) 
        {
            augmentedMatrix[lead][j] /= pivot;
        }

        // Eliminate entries above and below the pivot
        for (size_t i = 0; i < rowCount; ++i) 
        {
            if (i != r) 
            {
                double factor = augmentedMatrix[i][r];
                for (size_t j = 0; j < 2 * columnCount; ++j) 
                {
                    augmentedMatrix[i][j] -= factor * augmentedMatrix[r][j];
                }
            }
        }
    }

    // Extract the right half (inverse matrix)
    for (size_t i = 0; i < rowCount; ++i) 
    {
        for (size_t j = 0; j < columnCount; ++j) 
        {
            matrix[i][j] = round(augmentedMatrix[i][j + columnCount] * 100) / 100;
        }
    }
}
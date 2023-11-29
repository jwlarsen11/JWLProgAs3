/*
	Jacob Larsen
	Part 2
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <Eigen/Dense>
#include <sciplot/sciplot.hpp>
#include <algorithm>

using namespace std;
using namespace Eigen;
using namespace sciplot;

void printMatrix(vector<vector<double>>& matrix);
void multiplyMatrices(vector<vector<double>> matrix1, vector<vector<double>> matrix2, vector<vector<double>>& matrixO);
void invertMatrix(vector<vector<double>>& matrix);
void graphRegressionLine(double mx, double b, vector<vector<double>> X, vector<vector<double>> Y);

int main()
{
    ifstream myfile;
    myfile.open("input2.txt");
    vector<vector<double>> matrixXT(2, vector<double>(4));
    vector<vector<double>> matrixX(4, vector<double>(2));
    vector<vector<double>> matrixY(4, vector<double>(1));
    vector<vector<double>> XTX(2, vector<double>(2));
    vector<vector<double>> XTY(2, vector<double>(1));
    vector<vector<double>> COE(2, vector<double>(1));

    cout << "Matrix X: \n";
    //for matrixX and matrixXT from file
    for (int i = 0; i < 4; i++)
    {
        matrixXT[0][i] = 1;
        matrixX[i][0] = 1;
        myfile >> matrixXT[1][i];
        matrixX[i][1] = matrixXT[1][i];
        cout << "1 " << matrixXT[1][i] << endl;
    }

    cout << "\nMatrix Y: \n";
    //for matrixY
    for (int i = 0; i < 4; i++)
    {
        myfile >> matrixY[i][0];
        cout << matrixY[i][0] << endl;
    }

    //multiplying XT * X
    multiplyMatrices(matrixXT, matrixX, XTX);
    cout << "\nXT*X: \n";
    printMatrix(XTX);

    //multipying XT * Y
    multiplyMatrices(matrixXT, matrixY, XTY);
    cout << "XT*Y: \n";
    printMatrix(XTY);

    //multiplying XTX-1 * XTY
    invertMatrix(XTX);
    multiplyMatrices(XTX, XTY, COE);
    cout << "Coefficient Matrix: \n";
    printMatrix(COE);

    //outputs
    cout << "Least squares regression line is:\ny = " << COE[0][0] << " + " << COE[1][0] << "x\n";
    graphRegressionLine(COE[0][0], COE[1][0], matrixX, matrixY);
}

//to plot a graph of the line
void graphRegressionLine(double b, double mx, vector<vector<double>> X, vector<vector<double>> Y)
{
    Vec x = linespace(1, 5, 100);
    Plot2D.plot;

    plot.xlabel("x");
    plot.ylabel("y");

    plot.xrange(0, 100);
    plot.yrange(0, 100);

    plot.drawCurve(y, mx, b);
    for (int i = 0; i < X.size(); i++)
    {
        plot.drawPoint(X[i][0], Y[i][0])
    }

    Figure fig = { {plot} };
    Canvas canvas = { {fig} };
    canvas.show();
}

//to multiply matrices of varying sizes
void multiplyMatrices(vector<vector<double>> matrix1, vector<vector<double>> matrix2, vector<vector<double>>& matrixO) 
{
    if (matrix1[0].size() != matrix2.size()) 
    {
        cout << "Error: Incompatible matrix dimensions for multiplication." << endl;
    }

    size_t rows1 = matrix1.size();
    size_t cols1 = matrix1[0].size();
    size_t cols2 = matrix2[0].size();

    for (size_t i = 0; i < rows1; ++i) {
        for (size_t j = 0; j < cols2; ++j) {
            for (size_t k = 0; k < cols1; ++k) {
                matrixO[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

//inverts a 2x2 matrix
void invertMatrix(vector<vector<double>>& matrix) 
{
    double a = matrix[0][0];
    double b = matrix[0][1];
    double c = matrix[1][0];
    double d = matrix[1][1];

    double determinant = a * d - b * c;

    double inverseFactor = 1.0 / determinant;

    vector<vector<double>> inverse(2, vector<double>(2, 0.0));
    inverse[0][0] = d * inverseFactor;
    inverse[0][1] = -b * inverseFactor;
    inverse[1][0] = -c * inverseFactor;
    inverse[1][1] = a * inverseFactor;

    matrix = inverse;
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
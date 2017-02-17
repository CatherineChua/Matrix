#include "stdafx.h"
#include "matrix.h"
#include <vector>
#include <iostream>

using namespace std;

vector< vector<double>>matrixA;
vector< vector<double>>matrixTemp;
vector<vector<double>> matrixL;
vector< vector<double>> matrixU;
vector<double> B;

matrix::matrix() 
{
	createMatrix(1, 1);
}
matrix::matrix(int r, int c)
{
	createMatrix(r, c);
}
matrix::matrix(int c)
{
	createB(c);
}

//creats NxN matrix filled with 0
void  matrix::createMatrix(int r, int c)
{
	nrows = r;
	ncols = c;
	for (int i = 0; i < r; i++)
	{
		vector<double> tempVector;
		for (int j = 0; j < c; j++)
		{
			tempVector.push_back(0);
		}
		matrixA.push_back(tempVector);
	}
}

void  matrix::createB(int c)
{
	for (int i = 0; i < c; i++)
	{
		B.push_back(0);
	}
}

void matrix::fillMatrix()
{
	double num;
	for (int i = 0; i < nrows; i++)
	{
		cout << "Enter " << i << "th row of values: ";
		for (int j = 0; j < ncols; j++)
		{
			cin >> num;
			matrixA[i][j] = num;
		}
	}
}

void matrix::fillB(int x)
{
	double num;
	cout << "Enter B values: ";
	for (int i = 0; i < x; i++)
	{
		cin >> num;
		B[i] = num;
	}
}

void matrix::print()
{
	for (int i = 0; i < nrows; i++)
	{
		for (int j = 0; j < ncols; j++)
		{
			cout << "\t" << matrixA[i][j];
		}
		cout << "\n";
	}
}

void matrix::getU()
{
	//creating temp matrix for matrix L
	for (int i = 0; i < ncols; i++)
	{
		vector<double> tempVector;
		for (int j = 0; j < ncols; j++)
		{
			tempVector.push_back(0);
		}
		matrixTemp.push_back(tempVector);
	}

	//---end temp matrix------

	//begin row reduction for matrix U

	matrixU = matrixA;
	double num, dem;
	for (int pivot = 0; pivot < ncols - 1; pivot++)
	{
		for (int c = pivot; c < ncols; c++)
		{
			for (int r = c; r < ncols; r++)
			{
				matrixTemp[r][c] = matrixU[r][c];
			}
		}
		for (int i = pivot+1; i < nrows; i++)
		{
			num = matrixU[i][pivot];
			dem = matrixU[pivot][pivot];
			for (int j = pivot; j < ncols; j++)
			{
				matrixU[i][j] = matrixU[i][j] -((num/dem)* matrixU[pivot][j]);
			}

		}
	}
	
	for (int i = 0; i < nrows; i++)
	{
		for (int j = 0; j < ncols; j++)
		{
			cout << "\t" << matrixU[i][j];
		}
		cout << "\n";
	}
}

void matrix::getL()
{
	matrixL = matrixTemp;
	
	double scale;
	for (int c = 0; c < ncols; c++)
	{
		scale = matrixTemp[c][c];
		for (int r = c; r < nrows; r++)
		{
			matrixL[r][c] = matrixL[r][c] / scale;
		}
	}

	for (int i = 0; i < nrows; i++)
	{
		for (int j = 0; j < ncols; j++)
		{
			cout << "\t" << matrixL[i][j];
		}
		cout << "\n";
	}
	
}

int matrix::getRow()
{ 
	return nrows;
}

int matrix::getCol()
{ 
	return ncols;
}

void matrix::det()
{
	double sumU = matrixU[0][0];
	double sumL = matrixL[0][0];
	double determinate; 
	for (int i = 1; i < nrows; i++)
	{
		sumU *= matrixU[i][i];
		sumL *= matrixL[i][i];
	}

	determinate = sumU * sumL;
	cout << determinate << "\n";
}

void matrix::solveX(int x)
{
	vector<double> z;
	for (int i = 0; i < x; i++)
	{
		z.push_back(0);
	}
	
	double sumZ = 0;

	for (int r = 0; r < x; r++)
	{
		for (int c = 0; c < x; c++)
		{
			sumZ = sumZ + (matrixL[r][c] * z[c]);

		}
		z[r] = ((B[r] - sumZ)/matrixL[r][r]);
		sumZ = 0;
	}

	////////////////////////////////////////////////////
	double sumX = 0;
	vector<double> ansX;
	for (int i = 0; i < x; i++)
	{
		ansX.push_back(0);
	}
	for (int r = x - 1; r>= 0; r--)
	{
		for (int c = x - 1; c>= 0; c--)
		{
			sumX = sumX + (matrixU[r][c] * ansX[c]);
		}
		ansX[r] = ((z[r] - sumX)/matrixU[r][r]);
		sumX = 0;
	}
	
	cout << "Answer for x values:  ";
	for (int i = 0; i < x; i++)
	{
		cout << "\t" << ansX[i];
	}
	cout << "\n";	
}






#pragma once
#include "stdafx.h"
#include <vector>
#include <iostream>


class matrix{
public:
	matrix();
	matrix(int m, int  n);
	matrix(int m);
	int  getRow();
	int  getCol();
	void fillMatrix();
	void fillB(int);
	void print();
	void getU();
	void getL();
	void det();
	void solveX(int);
private:
	void  createMatrix(int, int);
	void createB(int);
	int  nrows, ncols;
	double  *data;
};

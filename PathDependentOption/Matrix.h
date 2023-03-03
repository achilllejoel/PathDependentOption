#pragma once
#ifndef Matrix_h
#define Matrix_h

#include <vector>

#include <iostream>
#include <fstream>

using namespace std;


typedef vector<double> Vector;
typedef vector<Vector> Matrix;

typedef vector<double> SamplePath; //SamplePath equi Vector
typedef vector<Vector> SamplePathBasket;


Vector operator*(const Matrix& C, const Vector& V);
Vector operator*(const double& a, const Vector& V);
Vector operator+(const double& a, const Vector& V);
Vector operator+(const Vector& V, const Vector& W);
Vector operator-(const double& a, const Vector& V);
Vector operator-(const Vector& V, const Vector& W);
Vector operator*(const Vector& V, const Vector& W);
Vector exp(const Vector& V);
double operator^(const Vector& V, const Vector& W);
double VectorSum (const Vector& V);

void operator>>(const SamplePath& S, ofstream * f);

#endif



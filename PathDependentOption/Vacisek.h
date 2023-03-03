#pragma once
#ifndef Vacisek_h
#define Vacisek_h

#include <vector>
#include <cstdlib>
#include <ctime>
#include "Matrix.h"

using namespace std;

class VacisekModel {
public:
    double r0;
    double kappa;
    double sigma;
    double theta;

    VacisekModel(double r0_, double kappa_, double theta_,double sigma_)  // constructor
    {
        r0 = r0_;
        kappa = kappa_;
        sigma = sigma_;
        theta = theta_;
        srand(time(NULL));
    }

    void GenerateSamplePath(double T, int m, SamplePath& R, SamplePath& ZBP);
    double B(double t, double T);
    double A(double t, double T);
    void GenerateRatesPath(int N, double T, int m);
};


#endif

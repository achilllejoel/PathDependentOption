#ifndef BSModel_h
#define BSModel_h

#include <vector>
#include <cstdlib>
#include <ctime>
#include "Matrix.h"

using namespace std;

typedef vector<double> SamplePath; //SamplePath equi Vector
typedef vector<Vector> SamplePathBasket;

class BSModel {
public:
    double S0;
    double r;
    double sigma;

    BSModel(double S0_, double r_, double sigma_)  // constructor
    {
        S0 = S0_; 
        r = r_; 
        sigma = sigma_;
        srand(time(NULL));
    }

    void GenerateSamplePath(double T, int m, SamplePath& S);
};

class BSModelBasket {
public:
    Vector S0, sigma;
    Matrix C;
    double r;

    BSModelBasket(Vector S0, double r, Matrix C);
    void GenerateSamplePath(double T, int m, SamplePathBasket& S);
};


#endif



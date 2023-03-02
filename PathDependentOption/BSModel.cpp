#include "BSModel.h"
#include <cmath>
#include <cstdlib>
#include <ctime>


const double pi = 4.0 * atan(1.0);

double Gauss()
{
    double U1 = (rand() + 1.0) / (RAND_MAX + 1.0);
    double U2 = (rand() + 1.0) / (RAND_MAX + 1.0);
    return sqrt(-2.0 * log(U1)) * cos(2.0 * pi * U2);
}

void BSModel::GenerateSamplePath(double T, int m, SamplePath& S)
{
    double St = S0;
    for (int k = 0; k < m; k++)
    {
        S[k] = St * exp((r - sigma * sigma * 0.5) * (T / m) + sigma * sqrt(T / m) * Gauss());
        St = S[k];
    }
}

Vector Gauss(int d)
{
    Vector Z(d);
    for (int j = 0; j < d; j++)
        Z[j] = Gauss();
    return Z;
}

BSModelBasket::BSModelBasket(Vector S0_, double r_, Matrix C_)
{
    this->S0 = S0_;
    this->r = r_;
    this->C = C_;
    srand(time(NULL));
    int d = S0_.size();
    sigma.resize(d);
    for (int j = 0; j < d; j++)
        sigma[j] = sqrt(C_[j] ^ C_[j]);
}

void BSModelBasket::GenerateSamplePath(double T, int m, SamplePathBasket& S)
{
    Vector St = S0;
    int d = S0.size();
    S.resize(m);
    for (int k = 0; k < m; k++)
    {
        S[k] = St * exp((T / m) * (r - 0.5 * sigma * sigma) + sqrt(T / m) * (C * Gauss(d)));
        St = S[k];
    }
}

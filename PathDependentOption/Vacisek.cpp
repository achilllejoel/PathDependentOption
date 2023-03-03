#include "BSModel.h"
#include "Vacisek.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

double VacisekModel::B(double t, double T) {   
    return (1 - exp(-kappa * (T - t))) / kappa;
};

double VacisekModel::A(double t, double T) {
    return exp((theta - (sigma * sigma)/(2* kappa* kappa)) * (B(t,T) - T + t) - sigma * sigma * B(t, T) * B(t, T) / (4*kappa));
};

void VacisekModel::GenerateSamplePath(double T, int m, SamplePath& R, SamplePath& ZBP)
{
    double rt = r0, E = 0, VaR = sigma * sigma;

    R[0] = r0;
    ZBP[0] = A(0, T) * exp(-B(0, T) * r0);

    for (int k = 1; k < m; k++)

    {
        E = rt * exp(-kappa * (T / m)) + theta * (1 - exp(-kappa * (T / m)));

        VaR = sigma * sigma * (1 - exp(-2 * kappa * (T / m))) / (2 * kappa);

        R[k] = E + sqrt(VaR) * Gauss();

        rt = R[k];

        ZBP[k] = A(k*T/m, T) * exp(-B(k * T / m, T) * rt);

    }
};

void VacisekModel::GenerateRatesPath(int N, double T, int m) {

    SamplePath R(m), ZBP(m);
    ofstream myfile, myfile2;
    ofstream *shortrate = &myfile, *zerocoupon = &myfile2;

    shortrate->open("shortrate.csv");
    zerocoupon->open("zerocoupon.csv");


    for (long i = 0; i < N; i++) {
        GenerateSamplePath(T, m, R, ZBP);
        R >> shortrate;
        ZBP >> zerocoupon;
    }
    shortrate->close();
    zerocoupon->close();

};


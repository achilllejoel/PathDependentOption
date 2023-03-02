#include <iostream>
#include <fstream>
#include "PathDepOption.h"
#include "GmtrAsianCall.h"
#include "ArthmAsianCall.h"
#include "EurCall.h"

using namespace std;

int MainArthmAsianCall()
{
    double S0 = 100.0, r = 0.03, sigma = 0.2;
    BSModel Model(S0, r, sigma);
    //ofstream out_file("./output.txt");

    double T = 1.0, K = 100.0;
    int m = 30;

    ArthmAsianCall Option(T, K, m);
    GmtrAsianCall CVOption(T, K, m);
    EurCall call(T, K);

    long N = 300000;
    cout << "European Call price = " << call.PriceByBSFormula(S0, sigma, r) << endl << "" << endl;
    CVOption.PriceByBSFormula(Model);
    cout << "Geometric call price by BS = " << CVOption.Price << endl;
    cout << "" << endl;

    CVOption.PriceByMC(Model,N);
    cout << "Geometric call price by MC = " << CVOption.Price << endl;
    cout << "Geometric call price by MC Error= " << CVOption.PricingError << endl << "" << endl;
    double GmtrAsianErr = CVOption.PricingError;

    Option.PriceByVarRedMC(Model, N, CVOption);

    cout << "Arithmetic call price variance reduction = " << Option.Price << endl
        << "Error = " << Option.PricingError << endl << "" << endl;
    double OptDiffErr = Option.PricingError;

    Option.PriceByMC(Model, N);
    cout << "Arithmetic Price by direct MC = " << Option.Price << endl
        << "Arithmetic Price by direct MC Error = " << Option.PricingError << endl << "" << endl;
    double ArithAsianErr = Option.PricingError;

    // Compute path correlation : 

    double PayoffCorr = (pow(ArithAsianErr, 2) + pow(GmtrAsianErr, 2) - pow(OptDiffErr,2))
        /(2*ArithAsianErr* GmtrAsianErr);

    cout << "PayoffPathCorr = " << PayoffCorr << endl;

    return 0;
}

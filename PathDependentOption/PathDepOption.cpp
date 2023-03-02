#pragma once
#include "PathDepOption.h"
#include "DifferenceOfOptions.h"
#include <cmath>
#include <iostream>
using namespace std;


double PathDepOption::PriceByMC(BSModel Model, long N) {
    double H = 0.0, Hsq = 0.0;
    SamplePath S(m);
    for (long i = 0; i < N; i++) {
        Model.GenerateSamplePath(T, m, S);
        H = (i * H + Payoff(S)) / (i + 1.0);
        Hsq = (i * Hsq + pow(Payoff(S), 2.0)) / (i + 1.0);
    }
    Price = exp(-Model.r * T) * H;
    PricingError = exp(-Model.r * T) * sqrt((Hsq - H * H) / sqrt(N - 1.0));
    return Price;
}


double PathDepOptionBasket::PriceByMC(BSModelBasket Model, long N)
{
    double H = 0.0, Hsq = 0.0;

    SamplePathBasket S(m);
    for (long i = 0; i < N; i++)
    {
        Model.GenerateSamplePath(T, m, S);
        H = (i * H + Payoff(S)) / (i + 1.0);
        Hsq = (i * Hsq + pow(Payoff(S), 2.0)) / (i + 1.0);
    }
    Price = exp(-Model.r * T) * H;
    PricingError = exp(-Model.r * T) * sqrt((Hsq - H * H) / sqrt(N - 1.0));

    return Price;

}


double PathDepOption::PriceByVarRedMC(BSModel Model, long N, PathDepOption& CVOption) {
    DifferenceOfOptions VarRedOpt(T, m, this, &CVOption);
    Price = VarRedOpt.PriceByMC(Model, N) + CVOption.PriceByBSFormula(Model);
    PricingError = VarRedOpt.PricingError;
    return Price;
}

double PathDepOptionBasket::PriceByVarRedMC(BSModelBasket Model, long N, PathDepOptionBasket& CVOption) {
    DifferenceOfBasketOptions VarRedOpt(T, m, this, &CVOption);
    Price = VarRedOpt.PriceByMC(Model, N) + CVOption.PriceByBSFormula(Model);
    PricingError = VarRedOpt.PricingError;
    return Price;
}


double EuropeanCallBasket::Payoff(SamplePathBasket& S)
{
    double Sum = 0.0;

    int d = S[0].size();

    Vector one(d);
    for (int i = 0; i < d; i++) {
        Sum = Sum + S[m - 1][i];
    }

    if (Sum < K) return 0.0;
    return Sum - K;
}

double SumEuropeanCall::Payoff(SamplePathBasket& S)
{
     int d = S[0].size();

    Vector PayoffVector(d);

    for (int i = 0; i < d; i++) {
        PayoffVector[i] = max(S[m - 1][i] - K[i], 0.0);
    }

    return VectorSum(PayoffVector);
}

double SumEuropeanCall::PriceByBSFormula(BSModelBasket Model)
{
    int d = Model.S0.size();

    Vector BSPrices(d);

    EurCall G(T, K[0]);

    for (int i = 0; i < d; i++) {
        G.K = K[i]; 
        BSPrices[i] = G.PriceByBSFormula(Model.S0[i], Model.sigma[i], Model.r);
    }

    return VectorSum (BSPrices);
}



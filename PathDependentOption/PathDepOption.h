#pragma once
#ifndef PathDepOption_h
#define PathDepOption_h

#include "BSModel.h"
#include "EurCall.h"

class PathDepOption {
public:
    double T, Price, PricingError;
    int m;
    virtual double Payoff(SamplePath& S) = 0;
    double PriceByMC(BSModel Model, long N);
    double PriceByVarRedMC(BSModel Model, long N, PathDepOption& CVOption);
    virtual double PriceByBSFormula(BSModel Model) { return 0.0; }
};


class PathDepOptionBasket
{
public:
    double T, Price, PricingError;
    int m;
    double PriceByMC(BSModelBasket Model, long N);
    virtual double Payoff(SamplePathBasket& S) = 0;
    double PriceByVarRedMC(BSModelBasket Model, long N, PathDepOptionBasket& CVOption);
    virtual double PriceByBSFormula(BSModelBasket Model) { return 0.0; }
};

class EuropeanCallBasket : public PathDepOptionBasket
{
public:
    double K;
    EuropeanCallBasket(double T_, double K_, int m_)
    {
        T = T_; K = K_; m = m_;
    }
    double Payoff(SamplePathBasket& S);
};

class SumEuropeanCall : public PathDepOptionBasket
{
public:
    Vector S0;
    Vector K;

    SumEuropeanCall(double T_, Vector K_, int m_)
    {
        T = T_; K = K_; m = m_;      
    }
    double Payoff(SamplePathBasket& S);

    double PriceByBSFormula(BSModelBasket Model);
};

#endif



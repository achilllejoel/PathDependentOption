#pragma once
#ifndef GmtrAsianCall_h
#define GmtrAsianCall_h

#include "PathDepOption.h"

class GmtrAsianCall : public PathDepOption {
public:
    double K;
    GmtrAsianCall(double T_, double K_, int m_)
    {
        this->T = T_;
        this->K = K_;
        this->m = m_;
    }
    double Payoff(SamplePath& S);
    double PriceByBSFormula(BSModel Model);
};

#endif

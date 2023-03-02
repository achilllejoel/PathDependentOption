#pragma once
#ifndef EurCall_h
#define EurCall_h

class EurCall {
public:
    double T, K;
    EurCall(double T_, double K_) { 
        T = T_; 
        K = K_; }
    double dplus(double S0, double sigma, double r);
    double dminus(double S0, double sigma, double r);
    double PriceByBSFormula(double S0, double sigma, double r);
    double VegaByBSFormula(double S0, double sigma, double r);
};

#endif

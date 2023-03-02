#pragma once
#ifndef ArthmAsianCall_h
#define ArthmAsianCall_h

#include "PathDepOption.h"

class ArthmAsianCall : public PathDepOption {
public:
    double K;
    ArthmAsianCall(double T_, double K_, int m_)
    {
        this->T = T_;
        this->K = K_;
        this->m = m_;
    }
    double Payoff(SamplePath& S);
};


class ArthmAsianCallBasket : public PathDepOptionBasket
{
public:
    double K;
    ArthmAsianCallBasket(double T_, double K_, int m_)
    {
        T = T_; K = K_; m = m_;
    }
    double Payoff(SamplePathBasket& S);
};

int MainArthmAsianCall(); 

#endif

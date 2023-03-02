#pragma once
#ifndef DifferenceOfOptions_h
#define DifferenceOfOptions_h

#include "PathDepOption.h"

class DifferenceOfOptions : public PathDepOption {
public:
    PathDepOption* Ptr1;
    PathDepOption* Ptr2;
    DifferenceOfOptions(double T_, int m_, PathDepOption* Ptr1_, PathDepOption* Ptr2_)
    {
        this->T = T_;
        this->m = m_;
        this->Ptr1 = Ptr1_;
        this->Ptr2 = Ptr2_;
    }
    double Payoff(SamplePath& S)
    {
        return Ptr1->Payoff(S) - Ptr2->Payoff(S);
    }
};



class DifferenceOfBasketOptions : public PathDepOptionBasket {
public:
    PathDepOptionBasket* Ptr1;
    PathDepOptionBasket* Ptr2;
    DifferenceOfBasketOptions(double T_, int m_, PathDepOptionBasket* Ptr1_, PathDepOptionBasket* Ptr2_)
    {
        this->T = T_;
        this->m = m_;
        this->Ptr1 = Ptr1_;
        this->Ptr2 = Ptr2_;
    }
    double Payoff(SamplePathBasket& S)
    {
        return Ptr1->Payoff(S) - Ptr2->Payoff(S);
    }
};



#endif

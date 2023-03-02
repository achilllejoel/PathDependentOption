#pragma once
#include "ArthmAsianCall.h"

double ArthmAsianCall::Payoff(SamplePath& S) {
    double Ave = 0.0;
    for (int k = 0; k < m; k++) {
        Ave = (k * Ave + S[k]) / (k + 1.0);
    }
    if (Ave < K) {
        return 0.0;
    }
    return Ave - K;
}

double ArthmAsianCallBasket::Payoff(SamplePathBasket& S)
{
    double Ave = 0.0;
    int d = S[0].size();
    Vector one(d);
    for (int i = 0; i < d; i++) one[i] = 1.0;
    for (int k = 0; k < m; k++)
    {
        Ave = (k * Ave + (one ^ S[k])) / (k + 1.0);
    }
    if (Ave < K) return 0.0;
    return Ave - K;
}


#include <iostream>
#include "PathDepOption.h"
#include "ArthmAsianCall.h"

using namespace std;

int MainBasketVarianceReduction()
{
    
    //MainArthmAsianCall(); 
    
    int d = 3;
    Vector S0(d);

    S0[0] = 40.0;
    S0[1] = 60.0;
    S0[2] = 100.0;
    
    double r = 0.03;
    
    Matrix C(d);
    for (int i = 0; i < d; i++)
        C[i].resize(d);
    
    C[0][0] = 0.1; C[0][1] = -0.1; C[0][2] = 0.0;
    C[1][0] = -0.1; C[1][1] = 0.2; C[1][2] = 0.0;
    C[2][0] = 0.0; C[2][1] = 0.0; C[2][2] = 0.3;
    

    C[0][0] = 0.1; C[0][1] = 0.0; C[0][2] = 0.0;
    C[1][0] = 0.0; C[1][1] = 0.2; C[1][2] = 0.0;
    C[2][0] = 0.0; C[2][1] = 0.0; C[2][2] = 0.3;

    BSModelBasket Model(S0, r, C);

    double T = 1.0 / 12.0, K = 200.0;
    
    int m = 30;
    
    ArthmAsianCallBasket Option(T, K, m);

    long N = 30000;
    cout << endl  << "Arithmetic Basket Call Price = " << Option.PriceByMC(Model, N) << endl;
    cout << "Arithmetic Basket Call Price MC Error= " << Option.PricingError << endl << "" << endl;


    EuropeanCallBasket Option2(T, K, m);
    cout << endl << "European Basket Call Price MC = " << Option2.PriceByMC(Model, N) << endl;
    cout << "European Basket Call Price MC Error= " << Option2.PricingError << endl << "" << endl;


    // Determining specific strikes
 
    double sum = VectorSum(S0);
    Vector Strikes(d);
    for (int j = 0; j < d; j++)
      {
        Strikes[j] = S0[j] * K / sum;
      }
    // End Specific Strikes
    
    
    SumEuropeanCall Option3(T, Strikes, m);

    Option3.PriceByBSFormula(Model);

    Option3.PriceByMC(Model, N);

    cout << endl << "Sum European Calls BS = " << Option3.PriceByBSFormula(Model) << endl;

    cout << endl << "Sum European Calls Price MC = " << Option3.PriceByMC(Model, N) << endl;
    cout << "Sum European  Calls Price MC Error= " << Option3.PricingError << endl << "" << endl;

    
    Option2.PriceByVarRedMC(Model, N, Option3);

    cout << endl << "European Basket Call Price Variance reduction technique = " << Option2.Price << endl;
    cout << "MC Error= " << Option2.PricingError << endl << "" << endl;

    return 0;
}

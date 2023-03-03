#include <iostream>
#include "PathDepOption.h"
#include "Vacisek.h"

using namespace std;

int main()
{
    double r0 = 0, kappa = 1, sigma = 0.2, theta = r0; // 

    double T=1.0/12; 

    int N = 1000, m = 30; // N number of simulations, m steps in the simulation. 

    VacisekModel V(r0, kappa, theta, sigma);

    cout << "Generating samples path ..." << endl;
    
    cout << " ...";
    
    V.GenerateRatesPath(N, T, m);
    
    cout << "End ! " << endl;
    
    return 0;
}

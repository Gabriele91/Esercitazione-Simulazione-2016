//
//  main.cpp
//  PI0-Simulazione-MMm
//
//  Created by Gabriele on 08/01/16.
//  Copyright © 2016 Gabriele. All rights reserved.
//

#include <iostream>
#include <cmath>

inline int factorial(int x)
{
    return (x <= 1 ? 1.0 : x * factorial(x - 1));
}

double compute_pi0(int m,double p)
{
    double sum = 0.0;
    for(int k = 0; k != m ; ++k)
    {
        sum += std::pow(m*p,k) / factorial(k);
    }
    sum += (std::pow(m*p,m) / factorial(m)) * (1/(1-p)) ;
    
    return std::pow(sum, -1.0);
}

double prob_coda_MMm(int m,double p)
{
    return compute_pi0(m,p) * (std::pow(m*p,m) / factorial(m)) * (1/(1-p));
}

double compute_pi_k(int k,int m, double p)
{
    if(k<=m)
    {
        return (std::pow(m*p,k) / factorial(k)) * compute_pi0(m,p);
    }
    return (std::pow(m,m)*std::pow(p,k) / factorial(m)) * compute_pi0(m,p);
}

int main(int argc, const char * argv[])
{
    // insert code here...
    std::cout << "PI0 = "               << compute_pi0(2,3./4.)      << "\n";
    std::cout << "PROB{coda} = "        << prob_coda_MMm(2,3./4.)    << "\n";
    std::cout << "PROB{non in coda} = " << 1.-prob_coda_MMm(2,3./4.) << "\n";
    return 0;
}

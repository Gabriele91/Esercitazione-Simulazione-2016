//
//  main.cpp
//  MG1-PASP-Simulazione
//
//  Created by Gabriele on 08/01/16.
//  Copyright © 2016 Gabriele. All rights reserved.
//

#include <iostream>
#include <vector>
#include <assert.h>

// SI PUO' USARE SIA CON MG1 CHE CON MM1
// basta che sia disciplinata con PASP
// r, numero lambda
// k, numero classi
double Tw_k(int r,
            int k,
            std::vector<double> l,
            std::vector<double> ts,
            std::vector<double> p)
{
    assert(k>=1);
    double up_sum = 0;
    double down_1_sum = 0;
    double down_2_sum = 0;
    for(int i=0; i!=r; ++i)   up_sum += l[i]*ts[i]*ts[i];
    for(int i=0; i!=k-1; ++i) down_1_sum += p[i];
    for(int i=0; i!=k; ++i)   down_2_sum += p[i];
    double up = (1./2.)*up_sum;
    double down = (1.-down_1_sum) * (1.-down_2_sum);
    return up / down;
}

int main(int argc, const char * argv[])
{
    std::vector<double> lambda = { 1./30. ,  1./60. };
    std::vector<double> ts     = { 14.,       20.   };
    std::vector<double> p      = { 7./15.,   1./3.  };
    int r = 2;
    int k = 0;
    
    //per la 1° classe
    k = 1;
    std::cout << "Tw_1 = "
              << Tw_k( r, k, lambda, ts, p )
              <<"\n";
    //per la 2° classe
    k = 2;
    std::cout << "Tw_2 = "
              << Tw_k( r, k, lambda, ts, p )
              <<"\n";
    return 0;
}

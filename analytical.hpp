#ifndef ANALYTICAL_H
#define ANALYTICAL_H

#include <iostream>
#include <string>
#include <cmath> 
#include <ctgmath>

class Analytical{

    private:
        float lambda;
        float mu;
        float M;
        float po;
        float l;
        float w;
        float lq;
        float wq;
        float rho;

    public:
        Analytical(float lambda, float mu, float M);
        void calculatePo();
        void calculateL();
        void calculateW();
        void calculateLQ();
        void calculateWQ();
        void calculateRho();
        void printResults();
        
};

#endif
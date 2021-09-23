/***************************************************************
  Student Name: Grayson Martin
  File Name: analytical.cpp
  Assignment number: Project #2

  This file calulates all the values needed by the analytical model. these values include Po, L, W, LQ, WQ, and Rho
***************************************************************/

#include "analytical.hpp"

/*
 * creates an analytical object with the necessary params used to calculate all the necessary values
 */
Analytical::Analytical(float lambda, float mu, float M){
    this->lambda = lambda;
    this->mu = mu;
    this->M = M;

    calculatePo();
    calculateL();
    calculateW();
    calculateLQ();
    calculateWQ();
    calculateRho();
}

/*
 * prints out the results of the analytical model
 */
void Analytical::printResults(){
    std::cout << "----- ANALYTICAL MODEL -----" << std::endl;
    std::cout << "  Po: " << po << std::endl;
    std::cout << "  L: " << l << std::endl;
    std::cout << "  W: " << w << std::endl;
    std::cout << "  LQ: " << std::fixed << lq << std::endl;
    std::cout << "  WQ: " << std::fixed << wq << std::endl;
    std::cout << "  Rho: " << rho << std::endl;
}

/*
 * calculates Po using the formula given on the project description's page.
 */
void Analytical::calculatePo(){
    float firstPart = 0;
    float secondPart = 0;
    float factorial = 1;

    for(int i = 0; i < M; i++){
        for(int j = 1; j < i + 1; j++){
            // for calculating factorial
            factorial *= j;
        }
        firstPart += (1 / factorial) * pow(lambda / mu, i);
    }

    factorial = 1;

    for(int i = 1; i < M + 1; i++){
        factorial *= i;
    }

    float temp1 = 1 / factorial;
    float temp2 = pow(lambda / mu, M);
    float temp3 = (M * mu) / (M * mu - lambda);
    secondPart = temp1 * temp2 * temp3;

    float result = 1 / (firstPart + secondPart);
    this->po = result;
}

/*
 * calculates L using the formula given on the project description's page.
 */
void Analytical::calculateL(){
    
    float numerator = (lambda * mu) * pow(lambda / mu, M);
    float factorial = 1;
    
    for(int i = 1; i < M; i++){
        factorial *= i;
    }

    float denom = factorial * pow(M * mu - lambda, 2);
    float result = (numerator / denom) * po + (lambda / mu);
    this->l = result;
}

/*
 * calculates W using the formula given on the project description's page.
 */
void Analytical::calculateW(){
    float result = l / lambda;
    this->w = result;
}

/*
 * calculates LQ using the formula given on the project description's page.
 */
void Analytical::calculateLQ(){
    float result = l - (lambda / mu);
    this->lq = result;
}

/*
 * calculates WQ using the formula given on the project description's page.
 */
void Analytical::calculateWQ(){
    float result = w - (1 / mu);
    this->wq = result;
}

/*
 * calculates Rho using the formula given on the project description's page.
 */
void Analytical::calculateRho(){
    float result = lambda / (M * mu);
    this->rho = result;
}

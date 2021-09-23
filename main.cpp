/***************************************************************
  Student Name: Grayson Martin
  File Name: main.cpp
  Assignment number: Project #2

  This file is used to create an instance of the simulation by getting user-inputted values
  The program then ensures the simulation runs until all arrivals are processed
***************************************************************/

#include "analytical.hpp"
#include "serviceCenter.hpp"
#include "customer.hpp"
#include <iomanip>

int main(){

    int numArrivals;
    int numServiceChannels;
    float avgArrivals;
    float avgServed;
    
    std::cout << "Enter n: ";
    std::cin >> numArrivals;
    std::cout << "Enter lambda: ";
    std::cin >> avgArrivals;
    std::cout << "Enter mu: ";
    std::cin >> avgServed;
    

    do{
        std::cout << "Enter M: ";
        std::cin >> numServiceChannels;
        
    }while(numServiceChannels > 10 || numServiceChannels < 1);

    Analytical newAnalytical(avgArrivals, avgServed, numServiceChannels);
    ServiceCenter simulation(numArrivals, avgArrivals, avgServed, numServiceChannels);

    while(!simulation.getPQIsEmpty()){ // runs until the PQ is empty, aka all the arrivals are processed
        simulation.processNextEvent();

        if(simulation.moreArrivals()){
            if(simulation.pqSize() <= simulation.getServiceChannels() + 1){ // if the PQ has less items than total service channels, fill up the PQ again
                simulation.addArrivals();
            }
        }
    }

    simulation.printResults();
    std::cout << std::endl;
    newAnalytical.printResults();

    return 0;

};

#ifndef SERVICECENTER_H
#define SERVICECENTER_H

#include "customer.hpp"
#include <queue>
#include <vector>
#include <iostream>
#include <random>
#include <time.h>
class ServiceCenter{

    private:
        //std::priority_queue<Customer, std::vector<float>, std::<greater<float> > queue;
        std::vector<Customer*> customers; // have to make a new vector with number of customers
        std::priority_queue <float, std::vector<float>, std::greater<float> > pq;
        std::queue <float> fifo;
        int serverAvailableCnt;
        int serviceChannels;
        int numArrivals;
        float avgArrivals;
        float avgServed;

        bool pqIsEmpty;
        int numWaited;
        float totalWaitTime;
        float totalServiceTime;
        float totalIdleTime;
        int customerIndex;
        float lastDeparture;

    public:
        ServiceCenter(int numArrivals, float avgArrivals, float avgServed, int serviceChannels);
        float getNextRandomInterval(float avg);
        void addArrivals();
        void processNextEvent();
        void processStatistics(Customer* customer); // currentWaitTime, customerWaitedCnt
        void printResults();
        float getW();
        float getWQ();
        float probWait();
        float getRho();
        float getPo();
        
        Customer* findCustomer(float time);
        int getServiceChannels();
        int getServerAvailableCnt();
        bool getPQIsEmpty();
        bool moreArrivals();
        int pqSize();

};

#endif
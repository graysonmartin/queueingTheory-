/***************************************************************
  Student Name: Grayson Martin
  File Name: serviceCenter.cpp
  Assignment number: Project #2

  A service center is basically the simulation we are trying to run. It contains the priority queue & the FIFO queue
  It starts by creating a vector of ALL the arrivals (n), then it processes them in groups of 200 (or less if there aren't that many left in the vector)
  It uses a negative exponential distribution to generate random intervals of time. We use these to assign values for arrival & departure times
***************************************************************/


#include "serviceCenter.hpp"
/*
 * creates a new service center object with the given params
 * initializes member variables to 0 in order to prevent future mishaps
 * seeds the randomizer (srand)
 * add the first 200 arrivals (or less if there aren't that many)
 * opens up all servers for business
 * @param numArrivals = number of customers that we will be processing
 * @param avgArrivals = avg number of arrivals per time period
 * @param avgServed = avg number of customers served per time period
 * @param serviceChannels = number of service channels
 */
ServiceCenter::ServiceCenter(int numArrivals, float avgArrivals, float avgServed, int serviceChannels){
    this->numArrivals = numArrivals;
    this->avgArrivals = avgArrivals;
    this->avgServed = avgServed;
    this->serviceChannels = serviceChannels;

    numWaited = 0;
    totalWaitTime = 0;
    totalServiceTime = 0;
    totalIdleTime = 0;
    customerIndex = 0;

    for(int i = 0; i < numArrivals; i++){
        customers.push_back(new Customer());
    }

    srand ((unsigned)time(NULL));
    addArrivals();
    serverAvailableCnt = serviceChannels;
}

/*
 *  generates random time intervals based off the parameter avg
 *  @param avg can be either avg number of arrivals or avg number of customers provided service in a given time frame
 */
float ServiceCenter::getNextRandomInterval(float avg){
    float randomFloat = (float) rand() / RAND_MAX;
    float intervalTime = -1 * (1.0 / avg) * log(randomFloat);

    return intervalTime;
}

/*
 * returns the current size of the priority queue
 * @return returns the size of priority queue  
 */
int ServiceCenter::pqSize(){
    return pq.size();
}

/*
 * adds customers from the customer vector to the priority queue
 * the number of customers added depends on how many are left in the priority queue
 * we ensure that the number of customers in the PQ will be less than 200 at all times
 * 
 */
void ServiceCenter::addArrivals(){

    int numCustomers = 0;

    if((customers.size() - customerIndex )<= 200){
        numCustomers = customers.size() - customerIndex;
    }
    else{
        numCustomers = 200;
    }

    int temp = customerIndex + numCustomers;

    for(int i = customerIndex; i < temp; i++){
        customers.at(i)->setArrivalTime(getNextRandomInterval(avgArrivals));
        pq.push(customers.at(i)->getArrivalTime());
    }

    customerIndex = customerIndex + numCustomers;
}

/*
 * checks to see if there are more arrivals that haven't been processed yet
 */
bool ServiceCenter::moreArrivals(){
    if(customerIndex != customers.size()){
        return true;
    }
    else{
        return false;
    }

}

/*
 * searches the customer vector for a customer with the given time
 * searches first for an arrival time first & then for a departure time
 * @return Customer* temp. pointer to a customer that will be necessary for later calculations
 */
Customer* ServiceCenter::findCustomer(float time){
    Customer* temp = nullptr;

    for(int i = 0; i < customers.size(); i++){ // first searches for the arrival time
        if(customers.at(i)->getArrivalTime() == time){
            temp = customers.at(i);
        }
    }

    if(temp == nullptr){
        for(int i = 0; i < customers.size(); i++){
            if(customers.at(i)->getDepartureTime() == time){ // searches for the depature time
                temp = customers.at(i);
            }
        }
    }
    return temp;
}

/*
 * returns the total number of service channels
 * @return number of service channels
 */
int ServiceCenter::getServiceChannels(){
    return serviceChannels;
}

/*
 * returns the number of available servers
 * @return number of available servers
 */
int ServiceCenter::getServerAvailableCnt(){
    return serverAvailableCnt;
}

/*
 * returns a bool of whether or not the PQ is empty. this is used by other classes and that's why we can't use the built-in .empty() function
 * @return a bool stating whether or not the pq is empty or not
 */
bool ServiceCenter::getPQIsEmpty(){
    if(pq.empty()){
        return true;
    }
    else{
        return false;
    }
}

/*
 * prints the results from the simulation.
 * these results include total wait time, number of customers that have waited, total service time, and total idle time
 * it also calculates W, WQ, Rho, and percentage of customers that have to wait.
 * po is not calculated because i'm unsure of how to do it.
 */
void ServiceCenter::printResults(){
    std::cout << "----- Simulation Data -----" << std::endl;
    std::cout << "  Total Wait Time: " << totalWaitTime << std::endl;
    std::cout << "  # of Customers Waited: " << numWaited << std::endl;
    std::cout << "  Total Service time: " << totalServiceTime << std::endl;
    std::cout << "  Total idle time: " << totalIdleTime << std::endl;
    std::cout << std::endl;

    std::cout << "  Po: " << getPo() << std::endl;
    std::cout << "  W: " << getW() << std::endl;
    std::cout << "  WQ: " << getWQ() << std::endl;
    std::cout << "  Rho: " << getRho() << std::endl;
    std::cout << "  % of Waiting: " << probWait() << "%" << std::endl;
}

/*
 *  returns the probability the customer has to wait
 *  @return formula to calculate the probability 
 */
float ServiceCenter::probWait(){
    return ((float)numWaited / (float)customers.size() * 100);
}

/*
 *  returns W, which is the average time a customer spends in the system
 *  @return formula to calculate the average time a customer spends in the system. 
 */
float ServiceCenter::getW(){
    return ((totalWaitTime + totalServiceTime) / customers.size());
}

/*
 *  returns Po, which is the percentage of time that no one is in the system
 *  @return formula to calculate the percentage of time that no one is in the system 
 */
float ServiceCenter::getPo(){
    return (1 / (lastDeparture * totalIdleTime) * 100);
}

/*
 *  returns WQ, which is the average time a customer spends waiting in the queue
 *  @return formula to calculate the average time a customer waits in the queue
 */
float ServiceCenter::getWQ(){
    return ((totalWaitTime) / numWaited);
}

/*
 *  returns Rho, which is the proportion of the system's resources that are used by the arrivals
 *  @return formula to calculate Rho
 */
float ServiceCenter::getRho(){
    return (totalServiceTime / (serviceChannels * lastDeparture));
}

/*
 * processes the next event by first checking if the event is an arrival, if it is, it will be processed
 * if the PQ is full, the arrival will be placed in the FIFO queue
 * 
 * if the event is not an arrival, it will be assumed as a departure and we will process it accordingly.
 * as soon as a departure occurs, we will check the FIFO queue if there are any events in there
 * if there are, we will add the item to the PQ
 */
void ServiceCenter::processNextEvent(){

    Customer* temp = findCustomer(pq.top()); 
    float interval = 0;
    float tempDepartTime = 0;

    if(!temp->getHasArrived()) { // the event is an arrival
        if(serverAvailableCnt > 0){
            serverAvailableCnt--;
            temp->setStartOfServiceTime(temp->getArrivalTime());
            interval = getNextRandomInterval(avgServed);
            temp->setDepartureTime(temp->getArrivalTime() + interval);
            temp->setHasArrived(true);
            pq.pop();
            pq.push(temp->getDepartureTime());
        }
        else{
            temp->setHasArrived(true);
            fifo.push(temp->getArrivalTime());
            pq.pop();
        }
    }
    else{ // the event is a departure
        serverAvailableCnt++;
        tempDepartTime = temp->getDepartureTime();
        pq.pop();

        if(!fifo.empty()){
            Customer* fifoTemp = findCustomer(fifo.front());
            fifoTemp->setStartOfServiceTime(tempDepartTime);
            fifoTemp->setWaitTime();
            interval = getNextRandomInterval(avgServed);
            fifoTemp->setDepartureTime(fifoTemp->getStartOfServiceTime() + interval);
            pq.push(fifoTemp->getDepartureTime());
            fifo.pop();
            serverAvailableCnt--; 
        }
        processStatistics(temp); 
        lastDeparture = temp->getDepartureTime(); // always sets the time of the last departure to the most recent event
    }

}

/*
 *  takes in a customer object and checks if the customer has been waiting in the FIFO queue, we will accumulate the time 
 *  this functions also keeps track of the total service time & the total idle time
 *  @param Customer* customer. the customer we are trying to extract information from 
 */
void ServiceCenter::processStatistics(Customer* customer){
    if(customer->getWaitTime() > 0){
        numWaited++; // increments number of customers that have waited
        //totalWaitTime = totalWaitTime + customer->getWaitTime();
        totalWaitTime = customer->getWaitTime(); // keep track of the total wait time
    }

    totalServiceTime = totalServiceTime + (customer->getDepartureTime() - customer->getStartOfServiceTime()); // keeps track of the total service time
    
    if(serverAvailableCnt == serviceChannels){ // iff all channels are empty, increment idle time
        totalIdleTime++;
    }
}

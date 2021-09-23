/***************************************************************
  Student Name: Grayson Martin
  File Name: customer.cpp
  Assignment number: Project #2

  This file defines all the customer member functions that are needed to keep track of all information regarding a customer.
***************************************************************/

#include "customer.hpp"

    /*
     * Creates a blank customer object. initializes waitTime to 0 and hasArrived to false
     */
    Customer::Customer(){
        waitTime = 0;
        hasArrived = false;
    }

    /*
    * setArrivalTime sets the customer's arrival time
    * @param float arrivalTime. new arrival time 
    */
    void Customer::setArrivalTime(float arrivalTime){
        this->arrivalTime = arrivalTime;
    }

    /*
    * setStartOfServiceTime sets the customer's start of service time
    * @param float startOfServiceTime. the time instance at which service begins on the customer's vehicle
    */
    void Customer::setStartOfServiceTime(float startOfServiceTime){
        this->startOfServiceTime = startOfServiceTime;
    }

    /*
    * setDepartureTime sets the customer's time of departure
    * @param float departureTime. the time at which the work is completed on the vehicle and the vehicle exists the service center
    */
    void Customer::setDepartureTime(float departureTime){
        this->departureTime = departureTime;
    }

    /*
    * setWaitTime sets the amount of time the customer had to wait equal to the start of service time minus their arrival time
    */
    void Customer::setWaitTime(){
        waitTime = startOfServiceTime - arrivalTime; 
    }

    /*
    * getArrivalTime returns the arrival time
    * @return returns the arrivalTime
    */
    float Customer::getArrivalTime(){
        return arrivalTime;
    }

    /*
    * getDepartureTime returns the departure time
    * @return returns the departureTime
    */
    float Customer::getDepartureTime(){
        return departureTime;
    }

    /*
    * getStartOfServiceTime returns the start of service time
    * @return returns the startOfServiceTime
    */
    float Customer::getStartOfServiceTime(){
        return startOfServiceTime;
    }

    /*
    * getHasArrived returns a bool whether or not the customer has arrived at the service center or not
    * this is used to distinguish between an arrival or a departure
    * @return returns a boolean stating whether or not the customer has already arrived
    */
    bool Customer::getHasArrived(){
        return hasArrived;
    }

    /*
    * getWaitTime returns the amount of time the customer had to wait
    * @return returns the waitTime
    */
    float Customer::getWaitTime(){
        return waitTime;
    }

    /*
    * setHasArrived sets if the customer has arrived or not
    * @param hasArrived determines if the customer has arrived or not
    */
    void Customer::setHasArrived(bool hasArrived){
        this->hasArrived = hasArrived;
    }
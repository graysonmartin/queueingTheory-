#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer{

    private:
        float arrivalTime;
        float startOfServiceTime;
        float departureTime;
        float waitTime;
        bool hasArrived;
    
    public:
        Customer();
        void setArrivalTime(float arrivalTime);
        void setStartOfServiceTime(float startOfServiceTime);
        void setDepartureTime(float departureTime);
        void setHasArrived(bool hasArrived);
        void setWaitTime();

        float getArrivalTime();
        float getStartOfServiceTime();
        float getDepartureTime();
        float getWaitTime();
        bool getHasArrived();

};

#endif
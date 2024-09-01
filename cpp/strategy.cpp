#include <iostream>

using namespace std;

class DrivingStrategy {
    public: 
        virtual void drive() = 0;
};

class FastDriving: public DrivingStrategy  {
    public: 
        void drive() {
            cout<<"driving fast"<<"\n";   
        }
};

class NormalDriving: public DrivingStrategy {
    public:
        void drive() {
            cout<<"driving normal"<<"\n";
        }
};

class Vehicle {
    DrivingStrategy* drivingStrategy;
    public:
    Vehicle(DrivingStrategy* drivingStrategy) {
        this->drivingStrategy = drivingStrategy;
    }

    void drive() {
        drivingStrategy->drive();
    }
};

class SportsVehicle: public Vehicle {
    public:
        SportsVehicle(): Vehicle(new FastDriving) {};
    
    void drive() {
        Vehicle::drive();
    }
};

class FamilyVehicle: public Vehicle {
    public:
        FamilyVehicle(): Vehicle(new NormalDriving) {};
    
    void drive() {
        Vehicle::drive();
    }
};

int main() {
    SportsVehicle sportsVehicle;
    FamilyVehicle familyVehicle;
    sportsVehicle.drive();
    familyVehicle.drive();
    return 0;
}

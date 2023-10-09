//
// Created by Ujjwal Shukla on 07/10/23.
//

#include <iostream>
#include <set>

using namespace std;

enum VehicleType {
    TwoWheeler,
    FourWheeler
};
class Vehicle {
    int vehicleNumber;
    VehicleType vt;
public:
    Vehicle(int vehicleNumber, VehicleType vt) {
        this->vehicleNumber = vehicleNumber;
        this->vt = vt;
    }
    void printVehicleInfo() {
        cout<<"number is " << vehicleNumber<<"\n";
    }
};




class ParkingSpot {
    Vehicle* vehicle;
    int id;
    int price;
    bool isEmpty;
public:
    ParkingSpot(int price, int id) {
        this->price = price;
        this->id = id;
        isEmpty = true;
    }
    void parkVehicle(Vehicle* vehicleToAssign) {
        if(!isEmpty) {
            throw "spot is not empty";
        }
        this->vehicle = vehicleToAssign;
        this->isEmpty = false;
    }
    void removeVehicle() {
        this->isEmpty = true;
        this->vehicle = nullptr;
    }
    int getId() {
        return this->id;
    }
    int getPrice() {
        return this->price;
    }
    bool isSlotEmpty() {
        return this->isEmpty;
    }
    Vehicle* getParkedVehicle() {
        return this->vehicle;
    }

};

class ParkingSpotStrategy {
public:
    virtual ParkingSpot* findSpot(set<ParkingSpot*> parkingSpotSet)  = 0;
};

class ParkingSpotDefaultStrategy: public ParkingSpotStrategy {
public:
    ParkingSpot* findSpot(set<ParkingSpot*> parkingSpotSet)  {
        for (ParkingSpot* parkingSpot: parkingSpotSet) {
            if(parkingSpot->isSlotEmpty()) {
                return parkingSpot;
            }
        }
        return nullptr;
    }
};

class TwoWheelerParkingSpot: public ParkingSpot {
public:
    TwoWheelerParkingSpot(int price, int id) : ParkingSpot(price, id) {}
};

class FourWheelerParkingSpot: public ParkingSpot {
public:
    FourWheelerParkingSpot(int price, int id) : ParkingSpot(price, id) {}
};

class ParkingSpotManager {
    set<ParkingSpot*> parkingSpots;
    ParkingSpotStrategy* parkingStrategy;
    ParkingSpot* getSpotById(int id) {
        for (auto parkingSpot : parkingSpots) {
            if (parkingSpot->getId() == id) {
                return parkingSpot;
            }
        }
        return nullptr;
    }
public:
    ParkingSpotManager(set<ParkingSpot*> parkingSpots, ParkingSpotStrategy* parkingStrategy) {
        this->parkingSpots = parkingSpots;
        this->parkingStrategy = parkingStrategy;
    }

    // can also return ID here
    int findParkingSpace() {
        auto spot =  this->parkingStrategy->findSpot(parkingSpots);
        if (spot == nullptr) {
            return -1;
        }
        return spot->getId();
    }

   void addNewParkingSpot(int id, int price) {
        auto parkingSpot = new ParkingSpot(price, id);
        parkingSpots.insert(parkingSpot);
    }

    void addVehicleToParkingSpot(Vehicle* vehicle, int id) {
        auto parkingSpot = this->getSpotById(id);
        parkingSpot->parkVehicle(vehicle);
    }
    Vehicle* removeVehicleFromParkingSpot(int id) {
        auto parkingSpot = this->getSpotById(id);
        auto vehicle = parkingSpot->getParkedVehicle();
        parkingSpot->removeVehicle();
        return vehicle;
    }
};

class TwoWheelerParkingSpotManager: public ParkingSpotManager {
public:
    TwoWheelerParkingSpotManager(set<ParkingSpot*> parkingSpots, ParkingSpotStrategy* parkingStrategy ) :
    ParkingSpotManager(parkingSpots, parkingStrategy) {};
};

class FourWheelerParkingSpotManager: public  ParkingSpotManager {
public:
    FourWheelerParkingSpotManager(set<ParkingSpot*> parkingSpots, ParkingSpotStrategy* parkingStrategy ) :
    ParkingSpotManager(parkingSpots, parkingStrategy) {};
};

class ParkingSpotManagerFactory {
   TwoWheelerParkingSpotManager* twoWheelerParkingSpotManager;
   FourWheelerParkingSpotManager* fourWheelerParkingSpotManager;
public:
    ParkingSpotManagerFactory() {
        set<ParkingSpot*> twoWheelerParkingSpots;
        set<ParkingSpot*> fourWheelerParkingSpots;
        this->twoWheelerParkingSpotManager = new TwoWheelerParkingSpotManager(twoWheelerParkingSpots , new ParkingSpotDefaultStrategy());
        this->fourWheelerParkingSpotManager = new FourWheelerParkingSpotManager(fourWheelerParkingSpots, new ParkingSpotDefaultStrategy());
    }
    ParkingSpotManager* getParkingSpotManager(VehicleType vt) {
        if (vt == TwoWheeler) {
            return twoWheelerParkingSpotManager;
        } else if (vt == FourWheeler) {
            return fourWheelerParkingSpotManager;
        }
        return nullptr;
    }
};

int main() {
    auto parkingSpotManagerFactory = new ParkingSpotManagerFactory();
    ParkingSpotManager* twoWheelerParkingSpotManager = parkingSpotManagerFactory->getParkingSpotManager(TwoWheeler);
    for (int i = 0; i < 3; ++i) {
        twoWheelerParkingSpotManager->addNewParkingSpot(100, i);
    }
    auto id = twoWheelerParkingSpotManager->findParkingSpace();
    if (id == -1) {
        cout<<"no parking spot";
    }
    cout<<"id is "<<id<<"\n";
    auto vehicle = new Vehicle(1234, TwoWheeler);
    twoWheelerParkingSpotManager->addVehicleToParkingSpot(vehicle, id);
    auto vehicleRemoved =  twoWheelerParkingSpotManager->removeVehicleFromParkingSpot(id);
    vehicleRemoved->printVehicleInfo();
    return 0;
}



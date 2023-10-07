//
// Created by Ujjwal Shukla on 07/10/23.
//

#include <iostream>
#include <set>

using namespace std;

enum vehicleType {
    TwoWheeler,
    FourWheeler
};
class Vehicle {
    int vehicleNumber;
    vehicleType vt;
public:
    Vehicle(int vehicleNumber, vehicleType vt) {
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
public:
    ParkingSpotManager(set<ParkingSpot*> parkingSpots, ParkingSpotStrategy* parkingStrategy) {
        this->parkingSpots = parkingSpots;
        this->parkingStrategy = parkingStrategy;
    }

    // can also return ID here
    ParkingSpot* findParkingSpace() {
        return this->parkingStrategy->findSpot(parkingSpots);
    }
    void addVehicleToParkingSpot(Vehicle* vehicle, ParkingSpot* parkingSpot) {
        parkingSpot->parkVehicle(vehicle);
    }
    Vehicle* removeVehicleFromParkingSpot(ParkingSpot* parkingSpot) {
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
    ParkingSpotManagerFactory(int twoWheelerSpots, int twoWheelerPrice, int fourWheelerSpots, int fourWheelerPrice) {
        set<ParkingSpot*> twoWheelerParkingSpots;
        for (int i = 0; i < twoWheelerSpots; ++i) {
            ParkingSpot* ps = new ParkingSpot(twoWheelerPrice, i);
            twoWheelerParkingSpots.insert(ps);
        }
        set<ParkingSpot*> fourWheelerParkingSpots;
        for (int i = 0; i < fourWheelerSpots; ++i) {
            ParkingSpot* ps = new ParkingSpot(fourWheelerPrice, i);
            fourWheelerParkingSpots.insert(ps);
        }
        this->twoWheelerParkingSpotManager = new TwoWheelerParkingSpotManager(twoWheelerParkingSpots, new ParkingSpotDefaultStrategy());
        this->fourWheelerParkingSpotManager = new FourWheelerParkingSpotManager(fourWheelerParkingSpots, new ParkingSpotDefaultStrategy());
    }
    ParkingSpotManager* getParkingSpotManager(vehicleType vt) {
        if (vt == TwoWheeler) {
            return twoWheelerParkingSpotManager;
        } else if (vt == FourWheeler) {
            return fourWheelerParkingSpotManager;
        }
        return nullptr;
    }
};

int main() {
    ParkingSpotManagerFactory* parkingSpotManagerFactory = new ParkingSpotManagerFactory(3, 100, 2, 400);
    ParkingSpotManager* parkingSpotManager = parkingSpotManagerFactory->getParkingSpotManager(TwoWheeler);
    auto spot = parkingSpotManager->findParkingSpace();
    if (spot == nullptr) {
        cout<<"no parking spot";
    }
    cout<<spot->getPrice()<<" "<< spot->getId()<<"\n";
    auto vehicle = new Vehicle(1234, TwoWheeler);
    parkingSpotManager->addVehicleToParkingSpot(vehicle, spot);
    auto vehicleRemoved =  parkingSpotManager->removeVehicleFromParkingSpot(spot);
    vehicleRemoved->printVehicleInfo();
    return 0;
}



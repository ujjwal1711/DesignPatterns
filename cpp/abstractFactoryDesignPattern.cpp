//
// Created by Ujjwal Shukla on 04/10/23.
//

#include<iostream>

enum company  {
    Toyota,
    Suzuki,
};

using namespace std;

class Car {
public:
    virtual void run()  = 0;
};

class Bike {
public:
    virtual void run() = 0;
};

class ToyotaBike: public Bike {
public:
    void run() {
        cout<<"run toyota bike"<<"\n";
    }
};

class SuzukiBike: public Bike {
public:
    void run() {
        cout<<"run suzuki bike"<<"\n";
    }
};

class ToyotaCar: public Car {
public:
    void run() {
        cout<<"run toyota car"<<"\n";
    }
};

class SuzukiCar: public Car {
public:
    void run() {
        cout<<"run suzuki car"<<"\n";
    }
};

class IVehicleFactory {
public:
    virtual Bike* createBike() = 0;
    virtual Car* createCar() = 0;
};

class ToyotaFactory: public IVehicleFactory {
public:
    Bike* createBike() {
        return new ToyotaBike();
    }
    Car * createCar() {
        return new ToyotaCar();
    }
};

class SuzukiFactory: public IVehicleFactory {
public:
    Bike* createBike() {
        return new SuzukiBike();
    }
    Car * createCar() {
        return new SuzukiCar();
    }
};

class CompanyAbstractFactory {
public:
    static IVehicleFactory* getFactory(company factory) {
        if (factory == Toyota) {
            return new ToyotaFactory();
        } else if (factory == Suzuki) {
            return new SuzukiFactory();
        }
        return nullptr;
    }
};

int main() {
    IVehicleFactory* vehicleFactory =CompanyAbstractFactory::getFactory(Toyota);
    Car* toyotaCar  = vehicleFactory->createCar();
    toyotaCar ->run();
    Bike* toyotaBike  = vehicleFactory->createBike();
    toyotaBike->run();
}

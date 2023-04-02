#include <iostream>

class Transport {
private:
    int maxSpeed;
public:
    Transport() {
        printf("Transport()\n");
    }
    int getMaxSpeed() {
        printf("Transport::getMaxSpeed()\n");
        return maxSpeed;
    }
    virtual void drive() = 0;
    ~Transport() {
        printf("~Transport()\n");
    }
};

class Motocycle : public Transport {
private:
    bool sidecarMotocycle;
public:
    Motocycle() {
        printf("Motocycle()\n");
    }
    void drive() override {
        printf("Motocycle::drive() override\n");
    }
    ~Motocycle() {
        printf("~Motocycle()\n");
    }
};

class Truck : public Transport {
private:
    int loadCapacity;
public:
    Truck() {
        printf("Truck()\n");
    }
    void drive() override {
        printf("Truck::drive() override\n");
    }
    ~Truck() {
        printf("~Truck()\n");
    }
};

class ElectricCar : public Transport {
private:
    int electricMotorCapacity;
public:
    ElectricCar() {
        printf("ElectricCar()\n");
    }
    void drive() override {
        printf("ElectricCar::drive() override\n");
    }
    ~ElectricCar() {
        printf("~ElectricCar()\n");
    }
};

int main()
{
    Transport* transport = new Truck();
    Truck truck;
    truck.getMaxSpeed();
    transport->drive();
}

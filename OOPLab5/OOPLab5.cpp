#include <iostream>

class Motor {
public:
    Motor() {
        printf("Motor()\n");
    }
    ~Motor() {
        printf("~Motor()\n");
    }
};

class ElectricMotor : public Motor {
private:
    int electricMotorCapacity;
public:
    ElectricMotor() {
        printf("ElectricMotor()\n");
    }
    ~ElectricMotor() {
        printf("~ElectricMotor()\n");
    }
};

class Transport {
protected:
    int maxSpeed;
    Motor* motor;
public:
    Transport() {
        printf("Transport()\n");
    }
    int getMaxSpeed() {
        printf("Transport::getMaxSpeed()\n");
        return maxSpeed;
    }
    virtual bool isInstance(std::string example) {
        return example == "Transport";
    }
    virtual void drive() = 0;
    virtual ~Transport() {
        printf("~Transport()\n");
    }
};

class Motocycle : public Transport {
public:
    Motocycle() {
        printf("Motocycle()\n");
    }
    void drive() override {
        printf("Motocycle::drive() override\n");
    }
    bool isInstance(std::string example) override{
        return example == "Motorcycle" || Transport::isInstance(example);
    }
    ~Motocycle() {
        printf("~Motocycle()\n");
    }
};

class SidecarMotocycle : public Motocycle {
public:
    SidecarMotocycle() {
        printf("~SidecarMotocycle()\n");
    }
    void drive() override {
        printf("SidecarMotocycle::drive() override\n");
    }
    bool isInstance(std::string example) override {
        return example == "SidecarMotocycle" || Motocycle::isInstance(example);
    }
    ~SidecarMotocycle() {
        printf("~SidecarMotocycle()\n");
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
    bool isInstance(std::string example) override {
        return example == "Truck" || Transport::isInstance(example);
    }
    ~Truck() {
        printf("~Truck()\n");
    }
};

class ElectricCar : public Transport {
public:
    ElectricCar() {
        printf("ElectricCar()\n");
        motor = new ElectricMotor();
    }
    void drive() override {
        printf("ElectricCar::drive() override\n");
    }
    bool isInstance(std::string example) override {
        return example == "ElectricCar" || Transport::isInstance(example);
    }
    ~ElectricCar() {
        printf("~ElectricCar()\n");
        delete motor;
    }
};

int main()
{
    srand(time(0));
    Transport* transport = new Truck();
    Truck truck;
    truck.getMaxSpeed(); // наследуемый метод
    transport->drive(); // перекрытый метод
    delete transport;
    
    ElectricCar electricCar;
    transport = new ElectricCar();
    delete transport; // утечка памяти не происходит, так как конструктор базового класса виртуальный

    Transport** transports = new Transport*[10];
    for (int i = 0; i < 10; ++i) {
        int choise = rand() % 3;
        printf("%d", choise);
        switch (choise) {
        case 0:
            transports[i] = new ElectricCar();
            break;
        case 1:
            transports[i] = new SidecarMotocycle();
            break;
        case 2:
            transports[i] = new Truck();
            break;
        }
    }
    // проверки на принадлежность некоторому классу
    for (int i = 0; i < 10; ++i) {
        if (transports[i]->isInstance("SidecarMotocycle")) {
            printf("Instance of SidecarMotocycle\n");
        }
        else if (transports[i]->isInstance("ElectricCar")) {
            printf("Instance of ElectricCar\n");
        }
        else if (transports[i]->isInstance("Truck")) {
            printf("Instance of Truck\n");
        }
    }
}

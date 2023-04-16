#include <iostream>

class Motor {
public:
    Motor() {
        printf("Motor()\n");
    }
    virtual void work() = 0;
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
    void work() override {

    }
    int getCapacity() {
        return electricMotorCapacity;
    }
    void changeCapacity(int value) {
        electricMotorCapacity = value;
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
    virtual std::string classname() {
        return "Transport";
    }
    virtual Motor* getMotor() {
        return motor;
    }
    virtual void drive() = 0;
    virtual ~Transport() {
        printf("~Transport()\n");
        delete motor;
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
    std::string classname() override {
        return "Motocycle";
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
    std::string classname() override {
        return "SidecarMotocycle";
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
    std::string classname() override {
        return "Truck";
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
    std::string classname() override {
        return "ElectricCar";
    }
    int getElectricMotorCapacity() {
        ElectricMotor* electricMotor = dynamic_cast<ElectricMotor*>(motor);
        if (electricMotor != nullptr) {
            return electricMotor->getCapacity();
        }
    }
    ~ElectricCar() {
        printf("~ElectricCar()\n");
    }
};

class TestParent {
public:
    TestParent() {
        printf("TestParent()\n");
    }
    void method1() {
        method2();
    }
    virtual void method2() {
        printf("TestParent::method2()\n");
    }
    void method3() {
        printf("TestParent::method3()\n");
    }
    ~TestParent() {
        printf("~TestParent()\n");
    }
};

class TestChild : public TestParent {
public:
    TestChild() {
        printf("TestChild()\n");
    }
    void method2() {
        printf("TestChild::method2()\n");
    }
    void method3() {
        printf("TestChild::method3()\n");
    }
    ~TestChild() {
        printf("~TestChild()\n");
    }
};

class Base {
protected:
    int id;
    static int counter;
public:
    Base() {
        id = counter++;
        printf("Base() %d\n", id);
    }
    Base(Base* obj) {
        id = counter++;
        printf("Base(Base*) %d\n", id);
    }
    Base(const Base& obj) {
        id = counter++;
        printf("Base(const Base&) %d\n", id);
    }
    Base& operator=(const Base& base) {
        printf("operator=\n");
        Base base1;
        return base1;
    }
    ~Base() {
        printf("~Base() %d\n", id);
    }
};

class Desc : public Base {
public:
    Desc() {
        printf("Desc() %d\n", id);
    }
    Desc(Desc* obj) {
        printf("Desc(Desc*) %d\n", id);
    }
    Desc(const Desc& obj) {
        printf("Desc(const Desc&) %d\n", id);
    }
    ~Desc() {
        printf("~Desc() %d\n", id);
    }
};

int Base::counter = 0;

namespace args {
    void func1(Base  obj) { 
        printf("args::func1()\n");
    };
    void func2(Base* obj) { 
        printf("args::func2()\n");
    };
    void func3(Base& obj) {
        printf("args::func3()\n");
    };
    void func4(std::unique_ptr<Base> obj) {
        printf("args::func4()\n");
    }
}

namespace returns {
    Base func1() { 
        Base base;
        printf("returns::func1()\n");
        return base;
    };
    Base* func2() { 
        Base base;
        printf("returns::func2()\n");
        return &base; // обращение к чужой памяти
    };
    Base& func3() {
        Base base;
        printf("returns::func3()\n");
        return base; // обращение к чужой памяти
    };
    Base func4() { 
        Base* base = new Base();
        printf("returns::func4()\n");
        return *base; // утечка памяти
    };
    Base* func5() { 
        Base* base = new Base();
        printf("returns::func5()\n");
        return base;
    };
    Base& func6() { 
        Base* base = new Base();
        printf("returns::func6()\n");
        return *base;
    };
    std::unique_ptr<Base> func7() {
        auto result = std::make_unique<Base>();
        printf("returns::func6()\n");
        return move(result);
    }
}

void uniqPtrFunc(std::unique_ptr<Base> ptr) {
    printf("uniqPtrFunc()\n");
}

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(0));

    Motocycle motocycle;
    motocycle.getMaxSpeed(); // Вызов наследуемого метода getMaxSpeed()
    motocycle.drive(); // Вызов перекрываемого метода drive()

    Transport* transport = new Truck();
    delete transport; // Работа виртуального деструктора

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
            printf("Capacity of electric motor: %d\n", static_cast<ElectricCar*>(transports[i])->getElectricMotorCapacity());
        }
        else if (transports[i]->isInstance("Truck")) {
            printf("Instance of Truck\n");
        }
        
        /*
        if (transports[i]->classname() == "SidecarMotocycle") {
            printf("Instance of SidecarMotocycle\n");
        }
        else if (transports[i]->classname() == "ElectricCar") {
            printf("Instance of ElectricCar\n");
            printf("Capacity of electric motor: %d\n", static_cast<ElectricCar*>(transports[i])->getElectricMotorCapacity());
        }
        else if (transports[i]->classname() == "Truck") {
            printf("Instance of Truck\n");
        }
        */
        /*
        ElectricCar* elCar = dynamic_cast<ElectricCar*>(transports[i]);
        if (elCar != nullptr) {
            elCar->getElectricMotorCapacity();
        }
        */
    }

    printf("----------\n");
    TestChild testChild;
    testChild.method1();
    printf("--- Работа с параметрами функции ---\n");
    
    Base* desc_d = new Desc();
    Desc desc_s;
    
    args::func1(desc_s);
    args::func2(desc_d);
    args::func3(*desc_d);
    printf("--- Конец работы с параметрами функции ---\n");
    printf("--- Работа с выводами функций ---\n");
    Base base1 = returns::func1();
    printf("----------\n");
    Base* base2 = returns::func2();
    printf("----------\n");
    Base base3 = returns::func3();
    printf("----------\n");
    Base base4 = returns::func4();
    printf("----------\n");
    Base* base5 = returns::func5();
    printf("----------\n");
    Base base6 = returns::func6();
    printf("----------\n");
    auto base7 = returns::func7();
    printf("--- Конец работы с выводами функций ---\n");
    

    std::unique_ptr<Base> uniquePtr= std::make_unique<Base>();
    uniqPtrFunc(std::move(uniquePtr));
    uniqPtrFunc(std::move(uniquePtr));
}

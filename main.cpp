#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <random>
#include <memory>

enum class Color{
    RED,
    GREEN,
    BLUE,
    GRAY,
    BLACK
};

std::ostream& operator<<(std::ostream& os, Color c) {
    switch (c) {
        case Color::RED:
            os << "Vermelha";
            break;

        case Color::GREEN:
            os << "Verde";
            break;

        case Color::BLUE:
            os << "Azul";
            break;

        case Color::GRAY:
            os << "Cinza";
            break;

        case Color::BLACK:
            os << "Preta";
            break;
    }
}

class Vehicle {
public:
    virtual std::string replenish() = 0;

    void printMe() {
        printMe("");
    }

    void printMe(const std::string& spacing) {
        std::cout   << spacing << "Nome:        " << name << '\n'
                    << spacing << "Capacidade:  " << capacity << (capacity>1?" pessoas":" pessoa") << '\n'
                    << spacing << "Reabastecer: " << replenish() << '\n'
                    << spacing << "Cor:         " << color << std::endl;
    }

protected:
    Vehicle(Color color, unsigned int capacity, std::string&& name) :
        color{color},
        capacity{capacity},
        name{std::move(name)}{}
    Color color;
    unsigned int capacity{};
    std::string name;
};

class Bicycle: public Vehicle {
public:
    explicit Bicycle() : Vehicle(Color::RED, 0, "Bycicle") {}
    explicit Bicycle(Color color) : Vehicle(color, 0, "Bycicle") {}
    std::string replenish() override {
        return "comer mais!";
    }
};

class GasCar: public Vehicle {
public:
    GasCar() : Vehicle(Color::GREEN, 4, "Carro a combustão") {}
    explicit GasCar(Color color) : Vehicle(color, 4, "Carro a combustão") {}
    std::string replenish() override {
        return "encher o tanque!";
    }
};

class ElectricCar: public Vehicle {
public:
    ElectricCar() : Vehicle(Color::BLUE, 4, "Carro Elétrico") {}
    explicit ElectricCar(Color color) : Vehicle(color, 4, "Carro Elétrico") {}
    std::string replenish() override {
        return "recarregar a bateria!";
    }
};

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<int> dist(1,3); // distribution in range [1, 3]
int randomNumber() {
    return dist(rng);
}

int main() {
    Bicycle bicycle{};
    GasCar gas_car{};
    ElectricCar electric_car{};

    bicycle.printMe();
    std::cout << std::endl;
    gas_car.printMe();
    std::cout << std::endl;
    electric_car.printMe();
    std::cout << std::endl;

    std::vector<std::unique_ptr<Vehicle>> vehicle_vector{};

    for(int i=0; i<10; ++i){
        switch (randomNumber()){
            case 1:
                vehicle_vector.push_back(std::make_unique<Bicycle>(Bicycle{}));
                break;
            case 2:
                vehicle_vector.push_back(std::make_unique<GasCar>(GasCar{}));
                break;
            case 3:
                vehicle_vector.push_back(std::make_unique<ElectricCar>(ElectricCar{}));
                break;
        }
    }
    std::cout << std::endl;

    std::cout << "Listando Vector:" << std::endl;
    for(int idx=0; const auto& v:vehicle_vector){
        std::cout << idx << ":";
        v->printMe("\t");
        idx++;
    }

    return 0;
}

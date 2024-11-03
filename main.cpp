#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <random>
#include <memory>
#include <map>

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
    return os;
}

class Tyre {
protected:
    Tyre(int max_km, int warning_max_km) : max_km(max_km), warning_max_km(warning_max_km){
        if (max_km > warning_max_km) {
            std::cout << "Tem certeza que vai durar mais que " << max_km << " km?" << std::endl;
        }
    }
    int max_km;
    int warning_max_km;
};

class BicycleTyre: public Tyre{
public:
    explicit BicycleTyre(int max_km) : Tyre(max_km, 3000){}
};

class CarTyre: public Tyre{
public:
    explicit CarTyre(int max_km) : Tyre(max_km, 30000) {}
};

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
                    << spacing << "Cor:         " << color << '\n'
                    << spacing << "#Pneus:      " << num_tyres << std::endl;
    }

protected:
    Vehicle(Color color, unsigned int capacity, std::string&& name, unsigned int num_tyres) :
        color{color},
        capacity{capacity},
        name{std::move(name)},
        num_tyres{num_tyres}{
    }
    Color color;
    unsigned int capacity{};
    std::string name;
    std::map<std::string, std::unique_ptr<Tyre>> map_tyres;
    unsigned int num_tyres;
};

class Bicycle: public Vehicle {
public:
    explicit Bicycle() : Vehicle(Color::RED, 0, "Bycicle", 2) {
        map_tyres["front"] = std::make_unique<BicycleTyre>(BicycleTyre{2500});
        map_tyres["back"] = std::make_unique<BicycleTyre>(BicycleTyre{2500});
    }
    explicit Bicycle(Color color) : Vehicle(color, 0, "Bicycle", 2) {}
    std::string replenish() override {
        return "comer mais!";
    }
};

class GasCar: public Vehicle {
public:
    explicit GasCar(unsigned int num_tyres) : Vehicle(Color::GREEN, 4, "Carro a combustão", num_tyres) {
        if(num_tyres < 4) {
            std::cerr << "num_tyres (" << num_tyres << ") can't be less than 4. exiting" << std::endl;
            std::exit(1);
        }
        map_tyres["left-front"] = std::make_unique<CarTyre>(CarTyre{25000});
        map_tyres["right-front"] = std::make_unique<CarTyre>(CarTyre{25000});
        map_tyres["left-back"] = std::make_unique<CarTyre>(CarTyre{25000});
        map_tyres["right-back"] = std::make_unique<CarTyre>(CarTyre{25000});
        if (num_tyres > 4) {
            map_tyres["spare"] = std::make_unique<CarTyre>(CarTyre{25000});
            if(num_tyres > 5) {
                std::cerr << "num_tyres is " << num_tyres << ". not enough space. exiting" << std::endl;
                std::exit(1);
            }
        }
    }
    explicit GasCar(Color color) : Vehicle(color, 4, "Carro a combustão", 4) {}
    std::string replenish() override {
        return "encher o tanque!";
    }
};

class ElectricCar: public Vehicle {
public:
    explicit ElectricCar(unsigned int num_tyres) : Vehicle(Color::BLUE, 4, "Carro Elétrico", num_tyres) {
        if(num_tyres < 4) {
            std::cerr << "num_tyres (" << num_tyres << ") can't be less than 4. exiting" << std::endl;
            std::exit(1);
        }
        map_tyres["left-front"] = std::make_unique<CarTyre>(CarTyre{25000});
        map_tyres["right-front"] = std::make_unique<CarTyre>(CarTyre{25000});
        map_tyres["left-back"] = std::make_unique<CarTyre>(CarTyre{25000});
        map_tyres["right-back"] = std::make_unique<CarTyre>(CarTyre{25000});
        if (num_tyres > 4) {
            map_tyres["spare"] = std::make_unique<CarTyre>(CarTyre{25000});
            if(num_tyres > 5) {
                std::cerr << "num_tyres is " << num_tyres << ". not enough space. exiting" << std::endl;
                std::exit(1);
            }
        }
    }
    explicit ElectricCar(Color color) : Vehicle(color, 4, "Carro Elétrico", 4) {}
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
    GasCar gas_car{5};
    ElectricCar electric_car{4};

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
                vehicle_vector.push_back(std::make_unique<GasCar>(GasCar{4}));
                break;
            case 3:
                vehicle_vector.push_back(std::make_unique<ElectricCar>(ElectricCar{5}));
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

#include <iostream>

using namespace  std;

class BasePizza {
public:
    virtual int cost() = 0;
};

class Margherita : public BasePizza {
public:
    int cost() {
        return 100;
    }
};

class FarmHouse: public BasePizza {
public:
    int cost() {
        return 200;
    }
};

class Topping : public BasePizza {

};

// "is a" as well as "has a" relationship
class Mushroom: public Topping {
    BasePizza* basePizza;
public:
    Mushroom(BasePizza* basePizza) {
        this->basePizza = basePizza;
    }
    int cost() {
        return this->basePizza->cost() + 20;
    }
};

class ExtraCheese: public Topping {
    BasePizza* basePizza;
public:
    ExtraCheese(BasePizza* basePizza) {
        this->basePizza = basePizza;
    }
    int cost() {
        return this->basePizza->cost() + 40;
    }
};

int main() {
   BasePizza* extraCheeseMargheritaPizzaWithMushroom = new Mushroom( new ExtraCheese( new Margherita()));
   cout<<"cost of extra cheese margherita pizza with mushrooms " << extraCheeseMargheritaPizzaWithMushroom->cost() << "\n";

    BasePizza* farmHousePizzaWithMushroom = new Mushroom( new FarmHouse());
    cout<<"cost of farmhouse pizza with mushrooms " << farmHousePizzaWithMushroom->cost() << "\n";

}


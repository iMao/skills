#include "pattern_factory.h"
#include <iostream>

namespace patterns {

void CheesePizza::Prepare() {
  std::cout << "Prepare of cheese pizza" << std::endl;
}

void CheesePizza::Bake() { std::cout << "Bake of cheese pizza" << std::endl; }

void CheesePizza::Cut() { std::cout << "Cut of cheese pizza" << std::endl; }

void CheesePizza::Box() { std::cout << "Box of cheese pizza" << std::endl; }

CheesePizza::~CheesePizza() {
  std::cout << "Object CheesePizza deleted" << std::endl;
}

void PepperoniPizza::Prepare() {
  std::cout << "Prepare of pepperoni pizza" << std::endl;
}

void PepperoniPizza::Bake() {
  std::cout << "Bake of pepperoni pizza" << std::endl;
}

void PepperoniPizza::Cut() {
  std::cout << "Cut of pepperoni pizza" << std::endl;
}

void PepperoniPizza::Box() {
  std::cout << "Box of pepperoni pizza" << std::endl;
}

PepperoniPizza::~PepperoniPizza() {
  std::cout << "Object PepperoniPizza deleted" << std::endl;
}

std::shared_ptr<Pizza> PizzaFactoryNY::CreatePizza(
    const std::string &pizza_type) {
  if (pizza_type == "cheese_pizza") return std::make_shared<CheesePizza>();
  if (pizza_type == "pepperoni_pizza")
    return std::make_shared<PepperoniPizza>();
  return nullptr;
}

PizzaFactoryNY::~PizzaFactoryNY() {
  std::cout << "Object PizzaFactoryNY deleted" << std::endl;
}

PizzaStore::PizzaStore(PizzaFactory *pizza_factory)
    : pizza_factory_(pizza_factory) {
  std::cout << "Object PizzaStore created" << std::endl;
}

PizzaStore::~PizzaStore() {
  std::cout << "Object PizzaStore deleted" << std::endl;
}

void PizzaStore::OrderPizza(const std::string &pizza_type) {
  std::shared_ptr<Pizza> pizza = pizza_factory_->CreatePizza(pizza_type);
  pizza->Prepare();
  pizza->Bake();
  pizza->Cut();
  pizza->Box();
}

}  // namespace patterns

#include <memory>

#include "src/patterns/pattern_factory.h"

int main() {
  patterns::PizzaFactoryNY pizza_factory_NY;
  patterns::PizzaStore pizza_store(&pizza_factory_NY);
  pizza_store.OrderPizza("cheese_pizza");
  pizza_store.OrderPizza("pepperoni_pizza");

  return 0;
}

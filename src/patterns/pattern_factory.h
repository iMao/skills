#ifndef SRC_PATTERNS_PATTERN_FACTORY_H
#define SRC_PATTERNS_PATTERN_FACTORY_H

#include <memory>

namespace patterns {

// interface of product
class Pizza {
 public:
  virtual void Prepare() = 0;
  virtual void Bake() = 0;
  virtual void Cut() = 0;
  virtual void Box() = 0;
  virtual ~Pizza() = default;
};

class CheesePizza : public Pizza {
 public:
  virtual void Prepare() override;
  virtual void Bake() override;
  virtual void Cut() override;
  virtual void Box() override;
  virtual ~CheesePizza() override;
};

class PepperoniPizza : public Pizza {
 public:
  virtual void Prepare() override;
  virtual void Bake() override;
  virtual void Cut() override;
  virtual void Box() override;
  virtual ~PepperoniPizza() override;
};

// interface of factory
class PizzaFactory {
 public:
  virtual std::shared_ptr<Pizza> CreatePizza(const std::string &pizza_type) = 0;
  virtual ~PizzaFactory() = default;
};

class PizzaFactoryNY : public PizzaFactory {
 public:
  virtual std::shared_ptr<Pizza> CreatePizza(
      const std::string &pizza_type) override;
  virtual ~PizzaFactoryNY() override;
};

// class of customer
class PizzaStore {
 public:
  PizzaStore() = delete;
  PizzaStore(PizzaFactory *pizza_factory);
  ~PizzaStore();
  void OrderPizza(const std::string &pizza_type);

 private:
  PizzaFactory *pizza_factory_;
};

}  // namespace patterns

#endif  // PATTERN_FACTORY_H

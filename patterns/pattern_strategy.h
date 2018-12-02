#ifndef C17_PATTERNS_PATTERN_STRATEGY_H
#define C17_PATTERNS_PATTERN_STRATEGY_H

#include <iostream>
#include <memory>

namespace patterns {

// interfaces of algorithms
class FlyBehavior {
 public:
  virtual void Fly() = 0;
  virtual ~FlyBehavior() = default;
};

class QuackBehavior {
 public:
  virtual void quack() = 0;
  virtual ~QuackBehavior() = default;
};

// classes which implement  FlyBehavior interface
class FlyWithWings : public FlyBehavior {
 public:
  void Fly() override { std::cout << "I am flying with wings" << std::endl; }
};

class FlyNone : public FlyBehavior {
 public:
  void Fly() override { std::cout << "I can not fly at all" << std::endl; }
};

// classes which implement  QuackBehavior interface
class Quack : public QuackBehavior {
 public:
  void quack() override { std::cout << "Quack" << std::endl; }
};

class Squeack : public QuackBehavior {
 public:
  void quack() override { std::cout << "Squeack" << std::endl; }
};

// fabric of objects which implement FlyBehavior interface
class FlyBehaviorFactory {
 public:
  std::shared_ptr<FlyBehavior> CreateFlyBehaviorObject(
      const std::string& type_of_fly) {
    if (type_of_fly == "FlyWithWings") {
      return std::make_shared<FlyWithWings>();
    }
    if (type_of_fly == "FlyNone") {
      return std::make_shared<FlyNone>();
    }
    return nullptr;
  }
};

// fabric of objects which implement QuackBehavior interface
class QuackBehaviorFactory {
 public:
  std::shared_ptr<QuackBehavior> CreateQuackBehaviorObject(
      const std::string& type_of_quack) {
    if (type_of_quack == "Quack") {
      return std::make_shared<Quack>();
    }
    if (type_of_quack == "Squeack") {
      return std::make_shared<Squeack>();
    }
    return nullptr;
  }
};

// abstract class
class Duck {
 public:
  Duck(const std::string& how_fly, const std::string& how_quack) {
    std::shared_ptr<FlyBehaviorFactory> fly_behavior_factory(
        new FlyBehaviorFactory);
    std::shared_ptr<QuackBehaviorFactory> quack_behavior_factory(
        new QuackBehaviorFactory);

    fly_behavior_ = fly_behavior_factory->CreateFlyBehaviorObject(how_fly);
    quack_behavior_ =
        quack_behavior_factory->CreateQuackBehaviorObject(how_quack);
  }

  virtual ~Duck() {}
  virtual void Display() {}
  void Swim() { std::cout << "I am swimming" << std::endl; }
  void PerfomFly() { fly_behavior_->Fly(); }
  void PerfomQuack() { quack_behavior_->quack(); }

 protected:
  std::shared_ptr<FlyBehavior> fly_behavior_;
  std::shared_ptr<QuackBehavior> quack_behavior_;
};

// concreat classes
class RedHeadDuck : public Duck {
 public:
  RedHeadDuck() = delete;
  RedHeadDuck(const std::string& how_fly, const std::string& how_quack)
      : Duck(how_fly, how_quack) {}
  virtual ~RedHeadDuck() override;
  void Display() override { std::cout << "This is RedHeadDuck" << std::endl; }
};

class RubberDuck : public Duck {
 public:
  RubberDuck() = delete;
  RubberDuck(const std::string& how_fly, const std::string& how_quack)
      : Duck(how_fly, how_quack) {}
  virtual ~RubberDuck() override;
  void Display() override { std::cout << "This is RubberDuck" << std::endl; }
};

}  // namespace patterns

#endif  // PATTERN_STRATEGY_H

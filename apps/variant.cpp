/**
 * C++17 std::variant<A,B,C>
 */

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>
#include <variant>

class Cat {
 public:
  Cat() = delete;
  Cat(const std::string& name) : name_(name) {}
  ~Cat() = default;
  void Meow() const { std::cout << name_ << " says Meow!\n"; }

 private:
  std::string name_;
};

class Dog {
 public:
  Dog() = delete;
  Dog(const std::string& name) : name_(name) {}
  ~Dog() = default;
  void Woof() const { std::cout << name_ << " says Woof!\n"; }

 private:
  std::string name_;
};

using Animal = std::variant<Dog, Cat>;

template <typename _Tp>
bool is_type(const Animal& a) {
  return std::holds_alternative<_Tp>(a);
}

struct AnimalVoice {
  void operator()(const Dog& d) const { d.Woof(); }
  void operator()(const Cat& c) const { c.Meow(); }
};

struct roots {
  roots() = default;
  double x1, x2;
};

std::variant<bool, roots> SolveEquation(double a, double b, double c) {
  double D = b * b - 4 * a * c;
  if (D < 0) {
    std::variant<bool, roots> answear{false};

    return answear;
  } else {
    std::variant<bool, roots> answear{roots()};

    std::get<roots>(answear).x1 = (-b + sqrt(D)) / (2.0 * a);
    std::get<roots>(answear).x2 = (-b - sqrt(D)) / (2.0 * a);

    return answear;
  }
}

int main() {
  std::list<Animal> animals{Cat{"Tabby"}, Dog{"Frend"}, Cat{"Sun"},
                            Dog{"Sharik"}};

  std::cout << "Sizeof(Dog):    " << sizeof(Dog) << std::endl;
  std::cout << "Sizeof(Cat):    " << sizeof(Cat) << std::endl;
  std::cout << "Sizeof(Animal): " << sizeof(Animal) << std::endl;
  std::cout << '\n';

  for (const Animal& a : animals) {
    std::cout << "index: " << a.index() << " ";
    std::visit(AnimalVoice{}, a);
  }

  std::cout << "There are "
            << std::count_if(std::begin(animals), std::end(animals),
                             is_type<Cat>)
            << " cats\n";
  std::cout << "There are "
            << std::count_if(animals.begin(), animals.end(), is_type<Dog>)
            << " dogs\n";

  std::cout << '\n';

  std::get<Dog>(*(++animals.begin())).Woof();
  std::get<Cat>(*animals.begin()).Meow();

  auto animal = *animals.begin();
  if (std::get_if<Dog>(&animal) == nullptr) {
    std::cout << "This animal is not Dog may be Cat\n";
  }

  if (std::get_if<Cat>(&animal) == nullptr) {
    std::cout << "This animal is not Cat may be Dog\n";
  }

  //-----------------Solving of square equation---------------------
  // roots posible
  //  double a = 2;
  //  double b = -10;
  //  double c = 2;

  // roots imposible
  double a = 10;
  double b = 10;
  double c = 20;

  auto result = SolveEquation(a, b, c);

  if (std::holds_alternative<bool>(result) && std::get<bool>(result) == false) {
    std::cout << "roots imposible\n";
  } else {
    std::cout << "roots posible: \n"
              << "x1: " << std::get<roots>(result).x1 << std::endl
              << "x2: " << std::get<roots>(result).x2 << std::endl;
  }

  return 0;
}

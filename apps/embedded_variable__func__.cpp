/**
 * Test C++11 feature embedded variable __func__
 */

#include <iostream>

void SomeUserFunction() {
  std::cout << "Function name: " << __func__ << std::endl;
}

class SomeUserClass {
 public:
  SomeUserClass() { std::cout << "Constructor: " << __func__ << std::endl; }
  SomeUserClass(const SomeUserClass& d) {
    std::cout << "Copy constructor: " << __func__ << std::endl;
  }
  ~SomeUserClass() { std::cout << "Destructor: " << __func__ << std::endl; }
  void Print() { std::cout << "UserFunction: " << __func__ << std::endl; }
};

class Functor {
 public:
  void operator()() { std::cout << "Functor: " << __func__ << std::endl; }
};

int main() {
  // feature: __func__ - содержит имя функции (встроенная переменная)
  SomeUserFunction();

  SomeUserClass df;
  df.Print();
  SomeUserClass d(df);

  auto f = [](const char* str) { std::cout << str << __func__ << std::endl; };
  f("lambda: ");

  Functor functor;
  functor();

  return 0;
}

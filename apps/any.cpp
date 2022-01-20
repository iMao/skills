/**
 * C++17 std::any
 */

#include <any>
#include <iomanip>
#include <iostream>
#include <vector>

class Stub {
 public:
  Stub(const std::string& name) : name_(name) {
    std::cout << "Stub(): " << name_ << "\n";
  }
  ~Stub() { std::cout << "~Stub(): " << name_ << "\n"; }

  std::string name_;
};

int main() {
  std::any a;

  if (!a.has_value()) {
    std::cout << "std::any a does not has a some value\n";
  }

  a = 10;
  std::cout << "std::any as int: " << std::any_cast<int>(a) << std::endl;

  a = 3.14f;
  std::cout << "std::any as float: " << std::any_cast<float>(a) << std::endl;

  if (a.type() == typeid(float)) {
    std::cout << "std::any has type float\n";
  }

  if (std::is_same<std::any, decltype(a)>::value) {
    std::cout << "variable a: has type std::any\n";
  }

  std::vector<int> vec{1, 2, 3};
  a = vec;

  if (a.type() == typeid(std::vector<int>)) {
    std::cout << "std::any has type std::vector<int>: ";
    for (auto& i : std::any_cast<std::vector<int>>(a)) {
      std::cout << i << " ";
    }
  }

  std::cout << '\n';

  std::string str{"Stub class"};
  a.emplace<Stub>(str);
  a.emplace<Stub>(std::string{"Empty Stub"});

  return 0;
}

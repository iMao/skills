/**
 * Generic lambda in C++14
 */
#include <algorithm>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

template <typename _Tp>
std::ostream& operator<<(std::ostream& os, const std::vector<_Tp>& vec) {
  for (auto& e : vec) {
    os << std::setw(5) << e << " ";
  }
  return os;
}

int main() {
  //-------------- generic lambda: [](auto p){}------------------
  auto divider = [](auto& e) { e /= 2; };

  std::vector<int> vec_int{0, 2, 2, 4, 4, 6, 6, 8, 8};
  std::vector<float> vec_float{2.2f, 4.4f, 2.6f, 6.8f};

  std::for_each(vec_int.begin(), vec_int.end(), divider);
  std::for_each(vec_float.begin(), vec_float.end(), divider);

  std::cout << "Vec<int>:   " << vec_int << std::endl;
  std::cout << "Vec<float>: " << vec_float << std::endl;

  //---------------concatenation [](auto, auto)->auto{}-----------
  auto glue = [](auto x, auto y) -> auto { return x + y; };
  std::string str1{"Hello "};
  std::string str2{"World!"};

  std::cout << "glue strings: " << glue(str1, str2) << std::endl;
  std::cout << "glue numbers: " << glue(3, 5) << std::endl;

  //---------------different types [](auto p, int i){}------------
  auto diff = [](auto p, int i) {
    while (i--) {
      std::cout << p << " ";
    }
    std::cout << std::endl;
  };

  diff("Hello", 3);
  diff(3.14, 3);

  //--------------rvalue type: [](auto&& x){}---------------------
  auto x = std::make_unique<double>(45.9);
  auto rvalue_x = [](auto&& x) -> auto {
    (*x) += 0.1;
    return std::move(x);
  };

  std::cout << "x: " << (*x) << " " << *(rvalue_x(x)) << std::endl;

  // -------------capture by reference---------------------------
  std::unique_ptr<int> int_ptr(new int(10));

  auto refvalue_cap = [&](int new_value) { *int_ptr = new_value; };

  std::cout << "init_value: " << *int_ptr << " ";
  refvalue_cap(15);
  std::cout << "new_value:  " << *int_ptr << std::endl;

  //--------------capture by value-------------------------------
  int a = 10;
  auto value = [=](int new_value) -> int { return a + new_value; };

  std::cout << "a: " << a << " value: " << value(2) << std::endl;

  //--------------capture rvalue---------------------------------
  auto ptr = std::make_unique<float>(3.14);
  auto get_value = [value = std::move(ptr)]() { return *value; };

  std::cout << "unique_ptr<float> : " << get_value() << std::endl;

  //-------------variadic generic lambda-------------------------
  std::cout << "variadic generic lambda:\n";

  auto variadic_generic_lambda = [](auto printer) {
    return [=](auto&&... ts)  // generic lambda, ts is a parameter pack
    {
      printer(std::forward<decltype(ts)>(ts)...);
      return [=] { printer(ts...); };  // nullary lambda (takes no parameters)
    };
  };
  auto p = variadic_generic_lambda([](auto v1, auto v2, auto v3) {
    std::cout << v1 << " " << v2 << " " << v3 << std::endl;
  });
  auto q = p(1, 'a', 3.14);  // outputs 1a3.14
  q();                       // outputs 1a3.14

  return 0;
}

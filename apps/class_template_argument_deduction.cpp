/**
 * C++17 class template argument deduction CTAD
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <string>
#include <tuple>
#include <vector>

template <typename T1, typename T2, typename T3>
struct Ctad {
  Ctad() : x_(0), y_(0), z_(0){};
  Ctad(T1 x, T2 y, T3 z) : x_(x), y_(y), z_(z) {}
  ~Ctad(){};
  T1 x_;
  T2 y_;
  T3 z_;
};

template <typename T>
struct Functor {
  Functor(T f) : f_(f) {}
  void operator()(int& i) { f_(i); }

  T f_;
};

int main() {
  // deduction types from initializers
  auto p = std::pair<int, std::string>(5, "CTAD");
  auto p_ = std::pair(5, "-CTAD-");

  auto t = std::tuple<int, float, bool, std::string>(2, 4.5f, true, "tuple");
  auto t_ = std::tuple(2, 4.5f, true, "tuple");

  auto vec = std::vector<int>(5);
  auto vec_ = std::vector{1, 2, 3, 4, 5};

  std::cout << "pair:  " << p_.first << " " << p_.second << std::endl;
  std::cout << "tuple: " << std::get<0>(t_) << " " << std::get<1>(t_) << " "
            << std::get<2>(t_) << " " << std::get<3>(t_) << " " << std::endl;

  // deduction types for new-operator
  auto ctad = new Ctad{5, 4.5, "Ctad"};
  std::cout << "Ctad: " << ctad->x_ << " " << ctad->y_ << " " << ctad->z_
            << std::endl;
  delete ctad;

  // function style deduction type
  std::mutex mut;
  { auto lg = std::lock_guard<std::mutex>(mut); }
  { auto lg_ = std::lock_guard(mut); }

  for (auto& e : vec_) {
    std::cout << e << " ";
  }

  std::cout << '\n';
  std::for_each(std::begin(vec_), std::end(vec_),
                Functor([&](int& i) { i *= 2; }));

  for (auto& e : vec_) {
    std::cout << e << " ";
  }

  std::cout << '\n';

  return 0;
}

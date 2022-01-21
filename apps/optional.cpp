/**
 * C++17 feature: std::optional<_Tp>()
 */

#include <assert.h>

#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <optional>

struct roots {
  double x1 = 0, x2 = 0;
};

std::optional<roots> SolveEquation(double a, double b, double c) {
  double D = b * b - 4 * a * c;
  if (D < 0) {
    return {};
  }
  roots ans;
  ans.x1 = (-b + std::sqrt(D)) / (2.0 * a);
  ans.x2 = (-b - std::sqrt(D)) / (2.0 * a);

  return {ans};
}

std::optional<roots> SolveEquation(double a, std::optional<double> ob,
                                   std::optional<double> oc) {
  double b = ob.value_or(0.0);
  double c = oc.value_or(0.0);

  return SolveEquation(a, b, c);
}

//----------------------------------------------------------------------
template <typename _Tp>
struct Roots {
  _Tp x1{};
  _Tp x2{};
};

template <typename _Tp, typename _Tr = Roots<_Tp>>
std::optional<_Tr> SolveEquation(_Tp a, std::optional<_Tp> const& ob,
                                 std::optional<_Tp> const& oc) {
  static_assert(
      std::is_same<_Tp, float>::value || std::is_same<_Tp, double>::value,
      "_Tp is not float or double");

  _Tp b = ob.value_or(0);
  _Tp c = oc.value_or(0);

  _Tp D = b * b - 4 * a * c;
  if (D < 0) {
    return {};
  }

  Roots<_Tp> ans;
  ans.x1 = (-b + std::sqrt(D)) / (2.0 * a);
  ans.x2 = (-b - std::sqrt(D)) / (2.0 * a);

  return {ans};
}

//------------------------------------------------------
struct Book {
  std::string header{};
  std::optional<std::string> sub_header{};
  std::string author{};
  int pages{};
  float price{};
};

//------------------------------------------------------
auto CreateReference(bool b) {
  static std::string msg{"C++17 standard"};

  return b ? std::optional<std::reference_wrapper<std::string>>(msg)
           : std::nullopt;
}

std::ostream& operator<<(std::ostream& os, Book const& book) {
  os << "Header: " << book.header << std::endl;
  if (book.sub_header) {
    os << "Sub header: " << book.sub_header.value() << std::endl;
  }
  os << "Author: " << book.author << std::endl;
  os << "Pages: " << book.pages << std::endl;
  os << "Price: " << book.price << std::endl;

  return os;
}

int main() {
  // roots posible
  double a = 2;
  double b = -10;
  double c = 2;

  // roots imposible
  double a1 = 10;
  double b1 = 10;
  double c1 = 20;

  auto solver = [](auto result) {
    std::cout << "Solving of square equation:\n";

    if (result) {
      std::cout << "x1: " << result.value().x1 << std::endl
                << "x2: " << result.value().x2 << std::endl;
    } else {
      std::cout << "roots imposible\n";
    }
    std::cout << std::endl;
  };

  solver(SolveEquation(a, b, c));

  solver(SolveEquation(a1, b1, c1));

  solver(SolveEquation(a1, {}, -c1));

  solver(SolveEquation(a1, {}, {}));

  // usage template<>---------------------------------------
  solver(SolveEquation<float, Roots<float>>(a, {}, {}));

  solver(SolveEquation<double, Roots<double>>(a, {}, -c));

  // special test static_assert
  // solver(SolveEquation<int, Roots<int>>(a, {}, {}));

  //--------------------------------------------------------

  Book book{.header = "Captain Blad",
            .sub_header = {},
            .author = "John Major",
            .pages = 325,
            .price = 3.65};

  Book book_{.header = "Captain Blad",
             .sub_header = "second edition",
             .author = "John Major",
             .pages = 350,
             .price = 5.65};

  std::cout << std::endl;

  std::cout << "Our store has: \n" << book << std::endl << book_ << std::endl;

  //--------------------------------------------------------
  auto print_reference = [](auto msg) {
    std::cout << "type: " << typeid(msg).name() << std::endl;

    if (msg.has_value()) {
      std::cout << msg->get() << std::endl;
    } else {
      std::cout << "msg empty" << std::endl;
    }
  };

  auto msg = CreateReference(true);

  print_reference(msg);

  return 0;
}

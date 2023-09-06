/**
 * C++14 feature: variable template
 */

#include <iomanip>
#include <iostream>

template <typename _Tp> constexpr _Tp pi = (_Tp)3.1415926535897932385;

template <typename _Tp> _Tp CircleSquare(_Tp radius) {
  return (pi<_Tp> * radius * radius);
}

template <typename _Tp> void Print(_Tp radius, _Tp circle_square) {
  std::cout << typeid(_Tp).name() << " radius: " << radius
            << " CircleSquare: " << circle_square << std::endl;
}

struct Limits {
  template <typename _Tp> static const _Tp min;

  template <typename _Tp> static const _Tp max;
};

template <typename _Tp> const _Tp Limits::min = _Tp(0.0);

template <typename _Tp> const _Tp Limits::max = _Tp(10.123452100210023002334);

template <typename _Tp> _Tp e = (_Tp)2.718281828;

int main() {
  float float_radius = 2.0f;
  double double_radius = 2.0;
  int int_radius = 2;

  auto float_circle_square = CircleSquare(float_radius);
  auto double_circle_square = CircleSquare(double_radius);
  auto int_circle_square = CircleSquare(int_radius);

  Print(float_radius, float_circle_square);
  Print(double_radius, double_circle_square);
  Print(int_radius, int_circle_square);

  //
  std::cout << typeid(Limits::min<float>).name() << " " << std::setw(25)
            << std::setprecision(20) << Limits::min<float> << std::endl;

  std::cout << typeid(Limits::max<float>).name() << " " << std::setw(25)
            << std::setprecision(20) << Limits::max<float> << std::endl;

  //

  std::cout << typeid(Limits::min<double>).name() << " " << std::setw(25)
            << std::setprecision(20) << Limits::min<double> << std::endl;

  std::cout << typeid(Limits::max<double>).name() << " " << std::setw(25)
            << std::setprecision(20) << Limits::max<double> << std::endl;

  std::cout << typeid(Limits::min<int>).name() << " " << std::setw(10)
            << Limits::min<int> << std::endl;

  std::cout << typeid(Limits::max<int>).name() << " " << std::setw(10)
            << Limits::max<int> << std::endl;

  std::cout << typeid(e<float>).name() << " " << std::setw(25)
            << std::setprecision(20) << e<float> << std::endl;

  std::cout << typeid(e<double>).name() << " " << std::setw(25)
            << std::setprecision(20) << e<double> << std::endl;

  return 0;
}

/**
 * usage using like typedef
 *
 */

#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

namespace geom {

template <typename _Tp>
using Vec2 = std::array<_Tp, 2>;

template <typename _Tp>
using Vec3 = std::array<_Tp, 3>;

template <typename _Tp>
_Tp ScalarMul(Vec2<_Tp> &a, Vec2<_Tp> &b) {
  return (a[0] * b[0] + a[1] * b[1]);
}

template <typename _Tp>
_Tp ScalarMul(Vec3<_Tp> &a, Vec3<_Tp> &b) {
  return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

}  // namespace geom

template <typename _Tp>
std::ostream &operator<<(std::ostream &os, geom::Vec2<_Tp> &vec) {
  return os << "<" << vec[0] << " , " << vec[1] << ">";
}

template <typename _Tp>
std::ostream &operator<<(std::ostream &os, geom::Vec3<_Tp> &vec) {
  return os << "<" << vec[0] << " , " << vec[1] << " , " << vec[2] << ">";
}

using real = long double;

int main() {
  // псевдонимы типа обьявленные с помощью using
  geom::Vec2<int> a{1, 2};
  geom::Vec2<int> b{3, 4};
  std::cout << a << " * " << b << " = " << geom::ScalarMul(a, b) << std::endl;

  real var = M_PI;
  std::cout << "real var: " << std::setw(23) << std::setprecision(20) << var
            << std::endl;

  return 0;
}

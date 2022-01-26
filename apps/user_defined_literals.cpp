/**
 * User-defined literals
 *
 */

#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14
#endif
using real = long double;
real operator"" _deg(real degree) { return degree * (M_PI / 180.0); }
real operator"" _km_hours(real km_hours) { return km_hours * 1000.0 / 3600.0; }
void operator"" _print(const char *s) { std::cout << s << std::endl; }
void operator"" _print(const char s) { std::cout << s << std::endl; }
void operator"" _print(real n) { std::cout << n << std::endl; }

int main() {
  //
  real radians = 90.0_deg;
  std::cout << "90 degree: " << radians << " radians" << std::endl;
  0x0ABDC_print;
  'A'_print;
  90.0_print;
  real m_sec = 820.0_km_hours;
  std::cout << "820 km/h: " << m_sec << " m/sec" << std::endl;

  return 0;
}

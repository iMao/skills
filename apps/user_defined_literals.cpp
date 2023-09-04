/**
 * User-defined literals
 *
 */

#include <chrono>
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14
#endif
using real = long double;
using UInt64 = unsigned long long;

real operator"" _deg(real degree) { return degree * (M_PI / 180.0); }
real operator"" _km_hours(real km_hours) { return km_hours * 1000.0 / 3600.0; }
UInt64 operator"" _km(real m) { return static_cast<UInt64>(m * 1000); }

void operator"" _print(real n) { std::cout << n << std::endl; }
void operator"" _print(const char *s) { std::cout << s << std::endl; }
void operator"" _print(const char s) { std::cout << s << std::endl; }

void operator"" _hex(UInt64 num) {
  std::cout <<"0x"<< std::hex << std::uppercase << num << std::endl;
}

template <typename T, typename Z>
std::ostream &operator<<(std::ostream &os,
                         std::chrono::duration<T, Z> &duration) {
  os << "time interval has: " <<std::dec<< duration.count() << " counts";
  return os;
}

int main() {
  // test user-defined literals
  real radians = 90.0_deg;
  real m_sec = 820.0_km_hours;
  UInt64 meters = 0.5_km;

  std::cout << "90 degree: " << radians << " radians" << std::endl;
  std::cout << "820 km/h:  " << m_sec << " m/sec" << std::endl;
  std::cout << "0.5 km:    " << meters << " meters" << std::endl;

  0x0ABDC_print;
  'A'_print;
  90.0_print;
  255_hex;

  // test standard literals
  using namespace std::chrono_literals;

  auto s = 30s;
  auto m = 0.5min;
  auto milsec = 10ms;
  auto usec = 0.5us;

  std::cout << "sec:             " << s << std::endl;
  std::cout << "minutes:         " << m << std::endl;
  std::cout << "milliseconds:    " << milsec << std::endl;
  std::cout << "microseconds:    " << usec << std::endl;

  return 0;
}

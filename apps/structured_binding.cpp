/*
 * C++17 structured binding
 */

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <tuple>

union Byte {
  struct {
    uint8_t bit0 : 1;
    uint8_t bit1 : 1;
    uint8_t bit2 : 1;
    uint8_t bit3 : 1;
    uint8_t bit4 : 1;
    uint8_t bit5 : 1;
    uint8_t bit6 : 1;
    uint8_t bit7 : 1;
  };
  uint8_t byte;
};

struct Data {
  Byte one;
  int number;
};

int main() {
  // structured binding for arrays

  int a[2]{1, 2};
  auto [x, y] = a;
  auto& [p, q] = a;

  std::cout << "x: " << x << "\ny: " << y << '\n';
  std::cout << "p: " << p << "\nq: " << q << '\n';
  std::cout << '\n';

  // structured binding for tuple

  auto tp = std::tuple(5, 3.5f, '$', "Hello");
  auto [int_var, float_var, char_var, const_char_var] = tp;

  std::cout << "int_var:        " << int_var << '\n';
  std::cout << "float_var:      " << float_var << '\n';
  std::cout << "char_var:       " << char_var << '\n';
  std::cout << "const_char_var: " << const_char_var << '\n';

  std::string s("structured binding");
  auto [i, f, str] = std::make_tuple(10, 2.5f, s);

  std::cout << '\n';
  std::cout << "i:   " << i << '\n';
  std::cout << "f:   " << f << '\n';
  std::cout << "str: " << str << '\n';

  // structured binding with struct{}

  Data data;
  data.number = 0xFFFF0000;
  data.one.byte = 0xF0;

  auto [byte, intnum] = data;

  std::cout << '\n';
  std::cout << "One byte: " << (byte.bit7 == 1 ? 1 : 0)
            << (byte.bit6 == 1 ? 1 : 0) << (byte.bit5 == 1 ? 1 : 0)
            << (byte.bit4 == 1 ? 1 : 0) << (byte.bit3 == 1 ? 1 : 0)
            << (byte.bit2 == 1 ? 1 : 0) << (byte.bit1 == 1 ? 1 : 0)
            << (byte.bit0 == 1 ? 1 : 0) << std::endl;

  std::cout << "intnum: " << std::hex << intnum << std::endl;

  return 0;
}

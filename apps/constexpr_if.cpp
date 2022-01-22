/**
 * C++17 std::constexpr_if ()
 */

#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>

template <typename _Tp>
constexpr _Tp pow(_Tp base, _Tp exp) {
  return (exp == 0 ? 1 : base * pow(base, exp - 1));
}

template <typename _Tp>
constexpr bool is_power2(const _Tp& value) {
  static_assert(std::is_same<_Tp, uint64_t>::value ||
                    std::is_same<_Tp, uint32_t>::value ||
                    std::is_same<_Tp, uint16_t>::value ||
                    std::is_same<_Tp, uint8_t>::value,
                "value is not unsigned");

  if ((value != 0) && ((value & (value - 1)) == 0)) {
    return true;
  }
  return false;
}

template <typename _Tp>
constexpr _Tp ReturnNearestPow2(const _Tp& value) {
  if (is_power2(value)) {
    return value;
  }

  int diff = 0;
  _Tp exp = 0;
  _Tp base = 2;

  do {
    exp++;
    diff = value - pow(base, exp);
  } while (diff >= 0);

  return pow(base, (exp - 1));
}

//--------------- if costexpr (const bool value){}----------------
template <typename _Tp>
auto value_of(_Tp value) {
  if constexpr (std::is_pointer_v<_Tp>) {
    return *value;
  } else {
    return value;
  }
}

template <typename _Tp>
void CheckValue(const _Tp& value) {
  if constexpr (std::is_arithmetic_v<_Tp>) {
    std::cout << "value is arithmetic type\n";
  }
  if constexpr (std::is_const_v<_Tp>) {
    std::cout << "value is const\n";
  }
  if constexpr (std::is_floating_point_v<_Tp>) {
    std::cout << "value is floating point type\n";
  }

  if constexpr (std::is_same_v<_Tp, int>) {
    std::cout << "Value is int\n";
  }

  if constexpr (std::is_same_v<_Tp, unsigned int>) {
    std::cout << "Value is unsigned int\n";
  }

  if constexpr (std::is_same_v<_Tp, float>) {
    std::cout << "Value is float\n";
  }
}

struct Book {
  std::string header;
  std::optional<std::string> sub_header;
  std::string author;
  int pages;
  float price;
};

template <std::size_t I>
auto get(const Book& book) {
  if constexpr (I == 0) {
    return book.header;
  } else if constexpr (I == 1) {
    return book.sub_header.value_or("---");
  } else if constexpr (I == 2) {
    return book.author;
  } else if constexpr (I == 3) {
    return book.pages;
  } else if constexpr (I == 4) {
    return book.price;
  }
}

constexpr uint32_t num = 25;

float fnum{3.14f};

int main() {
  int a = 5;

  typedef int* intptr;
  intptr p = &a;

  std::cout << "value_of(" << value_of(a) << ") :" << a << std::endl;
  std::cout << "value_of(" << value_of(p) << ") :" << a << std::endl;

  std::cout << "Nearest pow2: \n";
  std::cout << num << " nearest pow2: " << ReturnNearestPow2(num) << std::endl;

  std::array<int, ReturnNearestPow2(num)> arr;
  std::cout << "Size of std::array: " << arr.size() << std::endl;
  std::cout << std::endl;

  CheckValue(num);
  CheckValue(fnum);

  Book book{.header = "Captain Blade",
            .sub_header = {},
            .author = "John Davidson",
            .pages = 300,
            .price = 5.3};

  std::cout << std::endl;
  std::cout << "Information about book:\n";
  std::cout << "Header:     " << get<0>(book) << '\n'
            << "sub header: " << get<1>(book) << '\n'
            << "author:     " << get<2>(book) << '\n'
            << "pages:      " << get<3>(book) << '\n'
            << "price:      " << get<4>(book) << '\n';

  return 0;
}

/*
 * C++17 Template parameters auto
 */

#include <iomanip>
#include <iostream>

template <auto val>
struct essence {
  using value_type = decltype(val);
  static constexpr value_type val_ = val;
};

using true_t = essence<true>;
using false_t = essence<false>;
using chr_t = essence<'a'>;
using i_t = essence<5>;

template <typename T, T a>
const char* CheckData(essence<a> data) {
  if (std::is_same_v<true_t, decltype(data)>) {
    return "true_t";
  }

  if (std::is_same_v<false_t, decltype(data)>) {
    return "false_t";
  }

  if (std::is_same_v<chr_t, decltype(data)>) {
    return "chr_t";
  }

  if (std::is_same_v<i_t, decltype(data)>) {
    return "i_t";
  }
  return "unknown type";
}

int main() {
  true_t truth;
  false_t lying;
  chr_t symbol;
  i_t integer;

  std::cout << CheckData(truth) << std::endl;
  std::cout << CheckData(lying) << std::endl;
  std::cout << CheckData(symbol) << std::endl;
  std::cout << CheckData(integer) << std::endl;

  return 0;
}

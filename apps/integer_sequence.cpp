/**
 * C++14 std::integer_sequence - содержит индексы для нетиповых параметров
 * шаблона
 */

#include <array>
#include <iostream>
#include <tuple>
#include <utility>

constexpr int SIZE{5};

template <typename Array, std::size_t... I>
auto ArrayToTupleImpl(Array &ar, std::index_sequence<I...>) {
  return std::make_tuple(ar[I]...);
}

template <typename _Tp, std::size_t Num,
          typename Indices = std::make_index_sequence<Num>>
auto ArrayToTuple(const std::array<_Tp, Num> &ar) {
  return ArrayToTupleImpl(ar, Indices{});
}

int main() {
  std::array<int, SIZE> arr{0, 2, 4, 6, 8};

  auto tpl = ArrayToTuple(arr);

  std::cout << "tuple: " << std::get<0>(tpl) << " " << std::get<1>(tpl) << " "
            << std::get<2>(tpl) << " " << std::get<3>(tpl) << " "
            << std::get<4>(tpl) << std::endl;

  auto index_sequence = std::make_index_sequence<SIZE>{};
  auto int_sequence = std::make_integer_sequence<int, 10>{};
  auto num_sequence = std::integer_sequence<uint8_t, 1, 1, 0, 4>{};

  std::cout << "index_sequence: " << index_sequence.size() << std::endl;
  std::cout << "int_sequence:   " << int_sequence.size() << std::endl;
  std::cout << "num_sequence:   " << num_sequence.size() << std::endl;

  if (std::is_same_v<decltype(num_sequence), uint8_t>) {
    std::cout << "type: uint8_t\n";
  }

  return 0;
}

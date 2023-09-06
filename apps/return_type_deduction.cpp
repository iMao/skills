/**
 * C++14 feature: return type deduction for functions
 */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

auto CheckState(int data) {
  if (data < 0) {
    return 3.0;
  } else {
    return 5.0;
  }
}

auto CalcValue(int i) {
  if (i == 1) {
    return i;
  } else {
    return CalcValue(i - 1) + i;
  }
}

template <typename _Tp> auto GenerateNumber(int n_times, _Tp min, _Tp max) {
  std::vector<_Tp> rnd_numbers;

  if (std::is_same<_Tp, int>::value) {
    std::cout << "_Tp: int\n";
  }

  if (std::is_same<_Tp, float>::value) {
    std::cout << "_Tp: float\n";
  }

  if (std::is_same<_Tp, double>::value) {
    std::cout << "_Tp: double\n";
  }

  for (int i = 0; i < n_times; i++) {
    if (typeid(_Tp) == typeid(int)) {
      auto rnd = min + std::rand() % ((int)max - (int)min + 1);
      rnd_numbers.push_back(rnd);
    } else if (typeid(_Tp) == typeid(float) || typeid(_Tp) == typeid(double)) {
      auto rnd =
          static_cast<_Tp>(min + std::rand() % ((int)max - (int)min + 1));
      rnd_numbers.push_back(rnd);
    }
  }

  auto rnd_index = rnd_numbers.size() / 2;

  return rnd_numbers.at(rnd_index);
}

int main() {
  auto result_1 = CheckState(-1);
  std::cout << "result_1: " << result_1 << std::endl;

  auto result_2 = CheckState(2);
  std::cout << "result_2: " << result_2 << std::endl;

  auto result_3 = CalcValue(5);
  std::cout << "result_3: " << result_3 << std::endl;

  std::cout << "\n";
  auto rnd_int_1 = GenerateNumber(10, 0, 100);
  auto rnd_int_2 = GenerateNumber(100, 0, 100);
  auto rnd_int_3 = GenerateNumber(1000, 0, 100);

  std::cout << '\n';
  std::cout << "rnd_int_1: " << rnd_int_1 << std::endl;
  std::cout << "rnd_int_2: " << rnd_int_2 << std::endl;
  std::cout << "rnd_int_3: " << rnd_int_3 << std::endl;

  std::cout << "\n";
  auto rnd_float_1 = GenerateNumber(10, 0.f, 100.f);
  auto rnd_float_2 = GenerateNumber(100, 0.0f, 100.0f);
  auto rnd_float_3 = GenerateNumber(1000, 0.0f, 100.0f);

  std::cout << '\n';
  std::cout << "rnd_float_1: " << std::setw(5) << rnd_float_1 << std::endl;
  std::cout << "rnd_float_2: " << std::setw(5) << rnd_float_2 << std::endl;
  std::cout << "rnd_float_3: " << std::setw(5) << rnd_float_3 << std::endl;

  return 0;
}

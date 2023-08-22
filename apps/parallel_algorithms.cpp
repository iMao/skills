/*
 * C++17 parallel algorithms
 */

#include <algorithm>
#include <cmath>
#include <execution>
#include <iostream>
#include <iterator>
#include <vector>

const int SIZE{100};

int main() {
  std::vector<float> vf;

  for (int i = 0; i < SIZE; i++) {
    vf.push_back(i * M_PI);
  }

  //
  std::cout << "Sequence execution: " << std::endl;
  std::for_each(std::execution::seq, vf.begin(), vf.end(),
                [](float& a) { a *= a; });
  std::copy(vf.begin(), vf.end(), std::ostream_iterator<float>(std::cout, " "));
  std::cout << std::endl;

  // parallel
  std::cout << "Parallel execution: " << std::endl;
  std::for_each(std::execution::par, vf.begin(), vf.end(),
                [](float& a) { a *= a; });
  std::copy(vf.begin(), vf.end(), std::ostream_iterator<float>(std::cout, " "));
  std::cout << std::endl;

  // parallel + SIMD
  std::cout << "Parallel+SIMD execution: " << std::endl;
  std::for_each(std::execution::par_unseq, vf.begin(), vf.end(),
                [](float& a) { a *= a; });
  std::copy(vf.begin(), vf.end(), std::ostream_iterator<float>(std::cout, " "));
  std::cout << std::endl;

  return 0;
}

/*
 * C++17 parallel algorithms
 */

#include <algorithm>
//#include <execution>
#include <iostream>
#include <vector>

const int SIZE{1000};

int main() {
  std::vector<float> vf;

  for (int i = 0; i < SIZE; i++) {
    vf.push_back(i);
  }

  std::for_each(vf.begin(), vf.end(), [](float& a) { a *= a; });
  //  std::for_each(std::execution::par, vf.begin(), vf.end(),
  //                [](float& a) { a *= a; });

  return 0;
}

/**
 * C++17 inline variables
 */
#include <iomanip>
#include <iostream>

#include "inline_vars.h"

extern float data[SIZE];

int main() {
  CalcSquares(radius, squares, SIZE);

  PrintResults();

  CopyData();

  std::cout << '\n';
  for (int i = 0; i < SIZE; i++) {
    std::cout << "s: " << std::setw(6) << squares[i] << " d: " << std::setw(6)
              << data[i] << std::endl;
  }

  return 0;
}

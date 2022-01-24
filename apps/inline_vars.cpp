#include "inline_vars.h"

#include <iostream>

float data[SIZE];

void PrintResults() {
  for (int i = 0; i < SIZE; i++) {
    std::cout << "r: " << radius[i] << " s: " << squares[i] << std::endl;
  }
}

void CopyData() {
  for (int i = 0; i < SIZE; i++) {
    data[i] = squares[i];
  }
}

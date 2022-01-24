#ifndef INLINE_VARS_H
#define INLINE_VARS_H

inline const int SIZE{10};

inline float pi{3.14};

inline float radius[SIZE]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

inline float squares[SIZE];

inline float CalcCircleSquare(float radius) noexcept {
  return pi * radius * radius;
}

inline void CalcSquares(float radius[], float squares[], int size) noexcept {
  for (int i = 0; i < size; i++) {
    squares[i] = CalcCircleSquare(radius[i]);
  }
}

void PrintResults();

void CopyData();

#endif  // INLINE_VARS_H

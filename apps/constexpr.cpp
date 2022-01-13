/**
 * feature constexpr
 *
 */

#include <array>
#include <iostream>

constexpr int A = 2;
constexpr int B = 4;
constexpr int Size = A * B;

// only one return operator in C++11
constexpr int pow(int base, int exp) noexcept {
  return (exp == 0 ? 1 : base * pow(base, exp - 1));
}

constexpr int Factorial(int n) noexcept {
  return (n <= 1 ? 1 : n * Factorial(n - 1));
}

// usage constexpr in templates
template <typename _Tp>
constexpr _Tp Avg(_Tp a, _Tp b) noexcept {
  return (a + b) / static_cast<_Tp>(2);
}

template <typename _Tp>
class Point {
 public:
  constexpr Point() : x_(0), y_(0) {}
  constexpr Point(_Tp x, _Tp y) : x_(x), y_(y) {}
  constexpr _Tp GetX() const { return x_; }
  constexpr _Tp GetY() const { return y_; }
  void SetX(_Tp x) { x_ = x; }
  void SetY(_Tp y) { y_ = y; }

 private:
  _Tp x_, y_;
};

template <typename _Tp>
constexpr Point<_Tp> CalcMidllePoint(const Point<_Tp>& a,
                                     const Point<_Tp>& b) noexcept {
  return {Avg(a.GetX(), b.GetX()), Avg(a.GetY(), b.GetY())};
}

template <typename _Tp>
std::ostream& operator<<(std::ostream& os, const Point<_Tp>& p) {
  return os << "point [x: " << p.GetX() << ", y: " << p.GetY() << "]";
}

// usage constexpr in compilation time
std::array<int, Size> numbers{0, 1, 2, 3, 4, 5, 6, 7};
std::array<int, Avg(A, B)> num_array{4, 6, 8};
std::array<int, pow(A, 2)> numbers_array{3, 5, 7, 9};
std::array<Point<int>, Size> points;

constexpr Point<float> p1(3.14f, 3.14f);
constexpr Point<float> p2(5.14f, 5.14f);
constexpr Point<float> midpoint = CalcMidllePoint(p1, p2);

int main() {
  std::cout << "constexpr point1:       " << p1 << std::endl;
  std::cout << "constexpr point2:       " << p2 << std::endl;
  std::cout << "constexpr midlle point: " << midpoint << std::endl;

  for (int i = 0; i < Size; i++) {
    points[i].SetX(i);
    points[i].SetY(i);
  }

  for (auto& p : points) {
    std::cout << p << std::endl;
  }

  // usage constexpr in runtime
  Point<int> a(4, 5);
  Point<int> b(6, 5);
  Point<int> mid = CalcMidllePoint(a, b);
  std::cout << "point a:       " << a << std::endl;
  std::cout << "point b:       " << b << std::endl;
  std::cout << "midlle point:  " << mid << std::endl;

  std::cout << "n = 5 n!: " << Factorial(5) << std::endl;

  return 0;
}

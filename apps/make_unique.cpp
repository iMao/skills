/*
 * C++14 feature: std::make_unique()
 */

#include <iomanip>
#include <iostream>
#include <memory>

constexpr int N{5};

template <typename _Tp>
class Vec3 {
 public:
  Vec3() : x_(0), y_(0), z_(0) {}
  Vec3(_Tp x, _Tp y, _Tp z) : x_(x), y_(y), z_(z) {}
  Vec3(const Vec3& vec3) {
    x_ = vec3.x_;
    y_ = vec3.y_;
    z_ = vec3.z_;
  }
  Vec3& operator=(Vec3& vec3) {
    x_ = vec3.x_;
    y_ = vec3.y_;
    z_ = vec3.z_;
    return *this;
  }
  ~Vec3() {
    x_ = 0;
    y_ = 0;
    z_ = 0;
  }
  _Tp GetX() const { return x_; }
  _Tp GetY() const { return y_; }
  _Tp GetZ() const { return z_; }

 private:
  _Tp x_, y_, z_;
};

template <typename _Tp>
std::ostream& operator<<(std::ostream& os, const Vec3<_Tp>& vec) {
  if (std::is_same<_Tp, unsigned char>::value) {
    os << "{ " << (int)vec.GetX() << ", " << (int)vec.GetY() << ", "
       << (int)vec.GetZ() << " }";

  } else {
    os << "{ " << vec.GetX() << ", " << vec.GetY() << ", " << vec.GetZ()
       << " }";
  }
  return os;
}

int main() {
  std::unique_ptr<Vec3<int>> v3ptr = std::make_unique<Vec3<int>>();
  std::unique_ptr<Vec3<float>> vf3ptr =
      std::make_unique<Vec3<float>>(3.2f, 2.1f, 7.8f);
  std::unique_ptr<Vec3<double>[]> vd3ptr = std::make_unique<Vec3<double>[]>(N);

  auto v3uchar_ptr = std::make_unique<Vec3<uint8_t>>(9, 2, 7);

  std::cout << *v3ptr << std::endl;
  std::cout << *vf3ptr << std::endl;
  std::cout << *v3uchar_ptr << std::endl;

  for (int i = 0; i < N; i++) {
    std::cout << vd3ptr[i] << " ";
  }
  std::cout << '\n';

  return 0;
}

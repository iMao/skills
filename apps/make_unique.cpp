/*
 * C++14 feature: std::make_unique()
 */

#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

constexpr int SIZE{5};

template <typename _Tp> class Vec3 {
public:
  Vec3() : x_(0), y_(0), z_(0) {}
  Vec3(_Tp x, _Tp y, _Tp z) : x_(x), y_(y), z_(z) {}
  Vec3(const Vec3 &vec3) {
    x_ = vec3.x_;
    y_ = vec3.y_;
    z_ = vec3.z_;
  }
  Vec3 &operator=(const Vec3 &vec3) {
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
std::ostream &operator<<(std::ostream &os, const Vec3<_Tp> &vec) {
  if (std::is_same_v<uint8_t, _Tp>) {
    os << "{ " << static_cast<int>(vec.GetX()) << ", "
       << static_cast<int>(vec.GetY()) << ", " << static_cast<int>(vec.GetZ())
       << " }";
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

  auto v3uchar_ptr = std::make_unique<Vec3<uint8_t>>(9, 2, 7);

  std::unique_ptr<Vec3<double>[]> vd3ptr =
      std::make_unique<Vec3<double>[]>(SIZE);

  std::unique_ptr<std::vector<Vec3<int>>> vec_vec =
      std::make_unique<std::vector<Vec3<int>>>();

  vec_vec->emplace_back(0, 2, -1);
  vec_vec->emplace_back(-5, -5, -5);
  vec_vec->emplace_back(0, 4, 2);

  std::cout << *v3ptr << std::endl;
  std::cout << *vf3ptr << std::endl;
  std::cout << *v3uchar_ptr << std::endl;

  for (int i = 0; i < SIZE; i++) {
    std::cout << vd3ptr[i] << " ";
  }
  std::cout << '\n';

  for (auto &vec : *vec_vec) {
    std::cout << vec << " ";
  }
  std::cout << '\n';

  return 0;
}

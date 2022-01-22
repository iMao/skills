/**
 * C++17 nested namespaces
 */

#include <cmath>
#include <cstdint>
#include <deque>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <optional>

namespace mao {

namespace math {

template <typename _Tuint>
_Tuint Avg(_Tuint a, _Tuint b) {
  static_assert(
      std::is_same_v<_Tuint, uint8_t> || std::is_same_v<_Tuint, uint16_t> ||
          std::is_same_v<_Tuint, uint32_t> || std::is_same_v<_Tuint, uint64_t>,
      "type is not unsigned int");

  return ((a & b) + ((a ^ b) >> 1));
}

template <typename T>
constexpr T pi = (T)3.14159265358979323846;

}  // namespace math

namespace dsp {

template <typename _Tp>
class signal {
 public:
  signal() = default;
  signal(std::initializer_list<_Tp> const& init_list) : data_(init_list) {}
  ~signal() { data_.clear(); }

  std::size_t size() const { return data_.size(); }

  _Tp& operator[](int i) { return data_[i]; }
  const _Tp operator[](int i) const { return data_[i]; }

 private:
  std::deque<_Tp> data_;
};

void MullSignal(mao::dsp::signal<uint32_t>& signal_, uint32_t k,
                const std::optional<float>& of);

}  // namespace dsp

}  // namespace mao

void mao::dsp::MullSignal(mao::dsp::signal<uint32_t>& signal_, uint32_t k,
                          std::optional<float> const& of) {
  for (int i = 0; i < signal_.size(); i++) {
    signal_[i] *= k;
    signal_[i] *= of.value_or(1);
  }
}

// C++17 nested namespaces
namespace mao::dsp {

template <typename T>
void Swap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}

}  // namespace mao::dsp

namespace mao::math {

template <typename _Tp>
constexpr _Tp e = (_Tp)2.718281828459045235;

}

int main() {
  std::initializer_list<uint32_t> init{1, 2,  4,  6,  8,  6,  10, 8,
                                       9, 10, 11, 12, 13, 14, 15};

  mao::dsp::signal adc(init);

  auto box_filter = [&]() {
    for (int i = 0; i < adc.size() - 1; i++) {
      adc[i] = mao::math::Avg(adc[i], adc[i + 1]);
    }
  };

  uint32_t m = 2;
  auto mull = [&](const std::optional<float>& of) {
    mao::dsp::MullSignal(adc, m, of);
  };

  auto lprint = [&]() {
    for (int i = 0; i < adc.size() - 1; i++) {
      std::cout << adc[i] << " ";
    }
    std::cout << std::endl;
  };

  box_filter();
  lprint();

  mull({});
  lprint();

  mull({mao::math::pi<float>});
  lprint();

  mull({mao::math::e<double>});
  lprint();

  return 0;
}

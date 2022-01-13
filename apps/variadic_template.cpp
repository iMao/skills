/**
 * Variadic template
 *
 */

#include <iostream>

//-------------------------------------------------------
void Print() {}

template <typename _Tp, typename... _Tps>
void Print(const _Tp& arg, const _Tps&... args) {
  std::cout << sizeof...(args) << " : " << arg << "\n";
  Print(args...);
}

//-------------------------------------------------------
template <typename _Tp>
void Tprinf(const _Tp& arg) {
  std::cout << arg << std::endl;
}

template <typename _Tp, typename... _Tps>
void Tprinf(const _Tp& arg, const _Tps&... args) {
  Tprinf(arg);
  Tprinf(args...);
}

//-------------------------------------------------------
// tuple with variadic templates
//-------------------------------------------------------
template <typename... _Tps>
struct tuple;

template <typename _Tp, typename... _Tps>
struct tuple<_Tp, _Tps...> : tuple<_Tps...> {
  tuple(_Tp head, _Tps... args) : tuple<_Tps...>(args...), head_(head) {}

  typedef _Tp value_type;
  typedef tuple<_Tps...> base_type;

  value_type head_;
  base_type& base_ = static_cast<base_type&>(*this);
};

template <>
struct tuple<> {};

//-------------getter<>::get()---------------------------------------
template <int I, typename _Tp, typename... _Tps>
struct getter {
  typedef typename getter<(I - 1), _Tps...>::return_type return_type;

  static return_type get(tuple<_Tp, _Tps...>& t) {
    return getter<(I - 1), _Tp, _Tps...>::get(t);
  }
};

template <typename _Tp, typename... _Tps>
struct getter<0, _Tp, _Tps...> {
  typedef typename tuple<_Tp, _Tps...>::value_type return_type;

  static return_type get(tuple<_Tp, _Tps...>& t) { return t.head_; }
};

//----------------get<>()-------------------------------------------
template <int I, typename _Tp, typename... _Tps>
typename getter<I, _Tp, _Tps...>::return_type get(tuple<_Tp, _Tps...>& t) {
  return getter<I, _Tp, _Tps...>::get(t);
}

int main() {
  Print(3.14, 100, "Variadic template", 'A', true);
  std::cout << '\n';
  Tprinf(3.14, 100, "Variadic template", 'A', true);

  std::cout << '\n';

  tuple<int, float, char> tp(3, 7.5f, 'A');

  std::cout << tp.head_ << " " << tp.base_.head_ << " " << tp.base_.base_.head_
            << "\n";
  std::cout << get<0>(tp) << " " << get<1>(tp) << " " << get<2>(tp) << "\n";
  std::cout << getter<0, int, float, char>::get(tp) << " "
            << getter<1, int, float, char>::get(tp) << " "
            << getter<2, int, float, char>::get(tp) << "\n";

  return 0;
}

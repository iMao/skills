/**
 * Variadic template
 *
 */

#include <iostream>
#include <string>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Print() {}

template <typename _Tp, typename... _Tps>
void Print(const _Tp &arg, const _Tps &... args) {
  std::cout << sizeof...(args) << " : " << arg << "\n";
  Print(args...);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template <typename _Tp> void Tprinf(const _Tp &arg) {
  std::cout << arg << std::endl;
}

template <typename _Tp, typename... _Tps>
void Tprinf(const _Tp &arg, const _Tps &... args) {
  Tprinf(arg);
  Tprinf(args...);
}

//------------------------------------------------------------------------------
// функция для вычисления произведения всех параметров
//------------------------------------------------------------------------------
template <typename T> T Mul(const T &arg) { return arg; }

template <typename T, typename... _T> T Mul(const T &arg, const _T &... args) {
  return (arg * Mul(args...));
}

//------------------------------------------------------------------------------
// функция для склеивания в строку всех параметров
//------------------------------------------------------------------------------
std::string gluestr{": "};
template <typename T> void Glue(const T &arg) {
  if constexpr (std::is_pointer_v<T> && std::is_same_v<const char *, T>) {
    gluestr.append(arg);
  } else if constexpr (std::is_same_v<char, T>) {
    char buf[2]{'\0', '\0'};
    buf[0] = arg;
    gluestr.append(buf);
  } else if constexpr (std::is_arithmetic_v<T>) {
    gluestr.append(std::to_string(arg));
  } else if constexpr (std::is_same_v<std::string, T>) {
    gluestr += arg;
  }
}

template <typename T, typename... _T>
void Glue(const T &arg, const _T &... args) {
  Glue(arg);
  Glue(args...);
}

//------------------------------------------------------------------------------
// tuple with variadic templates
//------------------------------------------------------------------------------
// template <typename... _Tps>
// struct tuple;
//
// template <typename _Tp, typename... _Tps>
// struct tuple<_Tp, _Tps...> : tuple<_Tps...> {
//  tuple(_Tp head, _Tps... args) : tuple<_Tps...>(args...), head_(head) {}
//
//  typedef _Tp value_type;
//  typedef tuple<_Tps...> base_type;
//
//  value_type head_;
//  base_type& base_ = static_cast<base_type&>(*this);
//};
//
// template <>
// struct tuple<> {};
//
////-------------getter<>::get()------------------------------------------------
// template <int I, typename _Tp, typename... _Tps>
// struct getter {
//  typedef typename getter<(I - 1), _Tps...>::return_type return_type;
//
//  static return_type get(tuple<_Tp, _Tps...>& t) {
//    return getter<(I - 1), _Tp, _Tps...>::get(t);
//  }
//};
//
// template <typename _Tp, typename... _Tps>
// struct getter<0, _Tp, _Tps...> {
//  typedef typename tuple<_Tp, _Tps...>::value_type return_type;
//
//  static return_type get(tuple<_Tp, _Tps...>& t) { return t.head_; }
//};
//
////----------------get<>()-----------------------------------------------------
// template <int I, typename _Tp, typename... _Tps>
// typename getter<I, _Tp, _Tps...>::return_type get(tuple<_Tp, _Tps...>& t) {
//  return getter<I, _Tp, _Tps...>::get(t);
//}

int main() {
  Print(3.14, 100, "Variadic template", 'A', true);
  std::cout << '\n';

  Tprinf(3.14, 100, "Variadic template", 'A', true);
  std::cout << '\n';

  std::cout << "Mul params: " << Mul(2, 3.14, -1, 10) << std::endl;

  Glue(std::string("Hello"), 3.14, 10, 'c');
  std::cout << "Glue params: " << gluestr << std::endl;

  //  tuple<int, float, char> tp(3, 7.5f, 'A');
  //
  //  std::cout << tp.head_ << " " << tp.base_.head_ << " " <<
  //  tp.base_.base_.head_
  //            << "\n";
  //  std::cout << get<0>(tp) << " " << get<1>(tp) << " " << get<2>(tp) << "\n";
  //  std::cout << getter<0, int, float, char>::get(tp) << " "
  //            << getter<1, int, float, char>::get(tp) << " "
  //            << getter<2, int, float, char>::get(tp) << "\n";

  return 0;
}

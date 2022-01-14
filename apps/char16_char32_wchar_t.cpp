/**
 * C++11 features: char16_t, char32_t,
 *  R"(raw string)", L"wchar_t string", u8"UTF-8 string",
 *  u"char16_t string", U"char32_t"
 */

#include <iostream>
#include <locale>

template <typename _Tp>
void SizeStrings(_Tp str[]) {
  std::cout << "sizeof(" << typeid(_Tp).name() << ") : " << sizeof(_Tp)
            << std::endl;
}

int main() {
  char c[] = "Hello char\0";
  wchar_t w[] = L"Hello wchar_t\0";
  char16_t u[] = u"Hello char16_t\0";
  char32_t U[] = U"Hello char32_t\0";

  std::cout.imbue(std::locale());

  SizeStrings(c);
  SizeStrings(w);
  SizeStrings(u);
  SizeStrings(U);

  return 0;
}

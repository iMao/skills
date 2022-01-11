/**
 * тестирование функций запроса на выравнивание
 * структур данных в памяти
 * alignas() - установка требований к выравниванию
 * alignof() - запрос, какое выравнивание сейчас
 */

#include <iostream>
#include <typeinfo>

template <typename _Tp>
void ShowAlignment(_Tp &data_structure) {
  std::cout << "sizeof( " << typeid(_Tp).name() << " ): " << sizeof(_Tp)
            << "  alignof( " << typeid(_Tp).name() << " ): " << alignof(_Tp)
            << std::endl;
}

// types with default alignment
struct CharGroupDefault {
  char a;
  char b;
  char c;
};

struct DifferentGroupDefault {
  char a;
  int b;
  char c;
};

struct BigMembersGroupDefault {
  long long int a;
  int b;
  char c;
};

// types with user-defined alignment
struct alignas(2) CharGroupAlignment {
  char a;
  char b;
  char c;
};

struct alignas(8) DifferentGroupAlignment {
  char a;
  int b;
  char c;
};

struct alignas(16) BigMembersGroupAlignment {
  long long int a;
  int b;
  char c;
};

int main() {
  CharGroupDefault chg;
  DifferentGroupDefault dfg;
  BigMembersGroupDefault bmg;

  CharGroupAlignment chga;
  DifferentGroupAlignment dfga;
  BigMembersGroupAlignment bmga;

  ShowAlignment(chg);
  ShowAlignment(dfg);
  ShowAlignment(bmg);

  std::cout << '\n';

  ShowAlignment(chga);
  ShowAlignment(dfga);
  ShowAlignment(bmga);

  return 0;
}

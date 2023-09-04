/**
 * тестирование функций запроса на выравнивание
 * структур данных в памяти
 * alignas() - установка требований к выравниванию
 * alignof() - запрос, какое выравнивание сейчас
 */

#include <iostream>
#include <typeinfo>

template <typename _Tp> void ShowAlignment(_Tp &data_structure) {
  std::cout << "sizeof( " << typeid(_Tp).name() << " ): " << sizeof(_Tp)
            << "  alignof( " << typeid(_Tp).name() << " ): " << alignof(_Tp)
            << std::endl;
}

//------------------------------------------------------------------------------
// types with default alignment
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
// types with user-defined alignment
//------------------------------------------------------------------------------
struct alignas(2) CharGroupAlignment {
  char a;
  char b;
  char c;
};

struct alignas(4) DifferentGroupAlignment {
  char a;
  int b;
  char c;
};

struct alignas(16) BigMembersGroupAlignment {
  long long int a;
  int b;
  char c;
};

//------------------------------------------------------------------------------
// alignment like POSIX style
//------------------------------------------------------------------------------
struct AlignedChars {
  char a;
  char b;
  char c;
} __attribute__((aligned(1)));

struct AlignedIntChars {
  char a;
  int b;
  char c;
} __attribute__((aligned(4)));

struct AlignedBigMember {
  long long int a;
  int b;
  char c;
} __attribute__((aligned(8)));

//------------------------------------------------------------------------------
// packed like POSIX style
//------------------------------------------------------------------------------
struct PackedChars {
  char a;
  char b;
  char c;
} __attribute__((packed));

struct PackedIntChars {
  char a;
  int b;
  char c;
} __attribute__((packed));

struct PackedBigMember {
  long long int a;
  int b;
  char c;
} __attribute__((packed));

int main() {
  CharGroupDefault chg;
  DifferentGroupDefault dfg;
  BigMembersGroupDefault bmg;

  CharGroupAlignment chga;
  DifferentGroupAlignment dfga;
  BigMembersGroupAlignment bmga;

  AlignedChars achg;
  AlignedIntChars aichg;
  AlignedBigMember abmg;

  PackedChars pchg;
  PackedIntChars ichg;
  PackedBigMember pbmg;

  std::cout << "\nDefault alignment" << '\n';

  ShowAlignment(chg);
  ShowAlignment(dfg);
  ShowAlignment(bmg);

  std::cout << "\nUser-defined alignment" << '\n';

  ShowAlignment(chga);
  ShowAlignment(dfga);
  ShowAlignment(bmga);

  std::cout << "\nPOSIX aligned" << '\n';

  ShowAlignment(achg);
  ShowAlignment(aichg);
  ShowAlignment(abmg);

  std::cout << "\nPOSIX packed" << '\n';

  ShowAlignment(pchg);
  ShowAlignment(ichg);
  ShowAlignment(pbmg);

  return 0;
}

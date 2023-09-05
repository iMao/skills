/**
 * C++11 features: char16_t, char32_t,
 *  R"(raw string)", L"wchar_t string", u8"UTF-8 string",
 *  u"char16_t string", U"char32_t string"
 */

#include <codecvt>
#include <iomanip>
#include <iostream>
#include <locale>
#include <string>

template <typename _Tp> void SizeOfTypes(_Tp c) {
  std::cout << "sizeof(" << typeid(_Tp).name() << ") : " << sizeof(_Tp)
            << std::endl;
}

void PrintHex(const unsigned char *ptr, int size) {
  for (int i = 0; i < size; i++) {
    std::cout << std::setw(2) << std::hex << static_cast<int>(ptr[i]) << " ";
  }
}

int main() {
  std::string char_str = "char string";       // char
  std::wstring wchar_str = L"wchar_t string"; // wchar_t

  std::u16string u16_str = u"This is char16_t string";           // char16_t
  std::u32string u32_str = U"This is char32_t string Привет";           // char32_t
  std::string raw_str = R"(\n\t\0\bRaw string\n)";               // raw string
  std::u32string china_str = U"你好中文。 我很高興打印此消息。"; // china sign

  SizeOfTypes(char_str[0]);
  SizeOfTypes(wchar_str[0]);
  SizeOfTypes(u16_str[0]);
  SizeOfTypes(u32_str[0]);
  SizeOfTypes(raw_str[0]);

  using ptrcuc = const unsigned char *;


  std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t>
      converter_char16_t_utf8;
  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>
      converter_char32_t_utf8;

  std::cout << '\n';
  std::cout <<"char string:     "<< char_str << std::endl;
  std::wcout <<"wchar_t string: "<< wchar_str << std::endl;
  std::cout <<"raw string:      "<< raw_str << std::endl;

  std::cout << "u16string: " << converter_char16_t_utf8.to_bytes(u16_str)
            << std::endl;
  std::cout << "china str: " << converter_char32_t_utf8.to_bytes(china_str)
            << std::endl;
  std::cout << "u32string: " << converter_char32_t_utf8.to_bytes(u32_str)
            << std::endl;

  std::cout << "\nASCII code:   ";
  PrintHex(reinterpret_cast<ptrcuc>(char_str.data()),
           char_str.size() * sizeof(char));

  // Attention!!!  BigEndian
  std::cout << "\nwchar_t code: ";
  PrintHex(reinterpret_cast<ptrcuc>(wchar_str.data()),
           wchar_str.size() * sizeof(wchar_t));

  std::cout << "\nUtf-16 code:  ";
  PrintHex(reinterpret_cast<ptrcuc>(u16_str.data()),
           u16_str.size() * sizeof(char16_t));

  std::cout << "\nUtf-32 code:  ";
  PrintHex(reinterpret_cast<ptrcuc>(u32_str.data()),
           u32_str.size() * sizeof(char32_t));

  std::cout << "\nASCII code for raw string:   ";
  PrintHex(reinterpret_cast<ptrcuc>(raw_str.data()),
           raw_str.size() * sizeof(char));

  return 0;
}

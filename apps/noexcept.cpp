/*
 * C++17 noexcept
 */

#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <vector>

typedef void (*noexceptionfunc)(int& a) noexcept;
typedef void (*exceptionfunc)(int& a);

void Div2(int& a) noexcept { a /= 2; }
void DivItself(int& a) {
  int b = a + 1;
  try {
    a = b / a;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

int main() {
  auto vec = std::vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  noexceptionfunc ptrf = Div2;
  std::for_each(vec.begin(), vec.end(), ptrf);
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  exceptionfunc ptrexf = DivItself;
  std::for_each(vec.begin(), vec.end(), ptrexf);
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));

  return 0;
}

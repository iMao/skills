/**
 * C++14 feature: std::quoted()
 *
 */

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::string in{"String with \" <citate> \" from 1700 year"};
  std::string out{};

  std::stringstream ss;

  std::cout << in << std::endl;

  ss << std::quoted(in);
  std::cout << ss.str() << std::endl;

  ss >> std::quoted(out);
  std::cout << out << std::endl;
  std::cout << std::endl;

  ss.str("");
  out.clear();
  in.clear();

  in = "String with $ <citate> $ from 1700 year";
  const char delim = '$';
  const char escape = '\\';

  ss << std::quoted(in, delim, escape);
  std::cout << ss.str() << std::endl;

  ss >> std::quoted(out, delim, escape);
  std::cout << out << std::endl;



  return 0;
}

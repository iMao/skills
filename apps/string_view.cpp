/**
 * C++17 std::string_view
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

std::string_view GetFileName(std::string_view str) {
  auto pos_slash = str.find_last_of('\\');
  auto pos_dot = str.find_last_of('.');

  return str.substr(pos_slash + 1, pos_dot - pos_slash - 1);
}

std::string_view GetClearString(std::string_view str) {
  auto pos_begin = str.find_first_not_of(' ');
  auto pos_end = str.find_last_not_of(' ');

  str.remove_suffix(str.length() - pos_end - 1);
  str.remove_prefix(pos_begin);

  return str;
}

int main() {
  const char* path{R"(D:\development\cmake-workspace\skills\CMakeLists.txt)"};
  std::string path_to_file{R"(D:\development\cmake-workspace\skills\src.cpp)"};

  std::cout << GetFileName(path) << std::endl;
  std::cout << GetFileName(path_to_file) << std::endl;

  std::vector<std::string> text{"Code:", "SOS", "Warning", "Caution",
                                "Be aware"};

  std::sort(std::begin(text), std::end(text),
            [](std::string_view lstr, std::string_view rstr) -> bool {
              return lstr < rstr;
            });

  std::cout << std::endl;
  for (std::string_view s : text) {
    std::cout << s << std::endl;
  }

  std::cout << std::endl;
  std::vector<const char*> words{" plane ",    " man",   "power ",
                                 " _  plane_", "ma n_ ", " po we r "};

  std::for_each(words.begin(), words.end(), [](std::string_view s) {
    std::cout << s << " :" << GetClearString(s) << std::endl;
  });

  return 0;
}

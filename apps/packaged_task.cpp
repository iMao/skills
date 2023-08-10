#include <future>
#include <iostream>
#include <string>
#include <vector>

using packaged_func = std::packaged_task<std::string(std::string)>;
using reversed_str = std::future<std::string>;
using worker = std::thread;

constexpr int NUMBER_TASKS{10};

std::string SimpleReverseString(std::string s);

int main() {

  std::vector<packaged_func> funcs;
  std::vector<reversed_str> result_strs;
  std::vector<worker> threads;
  std::vector<std::string> original_strs{"Hello", "{(^&",  "memory", "library",
                                         "force", "ship",  "juice",  "kiss",
                                         "12345", "signal"};

  for (int i = 0; i < NUMBER_TASKS; i++) {
    funcs.emplace_back(SimpleReverseString);
  }

  for (auto &ptask : funcs) {
    result_strs.emplace_back(ptask.get_future());
  }

  for (int i = 0; i < NUMBER_TASKS; i++) {
    threads.emplace_back(std::move(funcs[i]), original_strs[i]);
  }

  for (auto &th : threads) {
    if (th.joinable()) {
      th.join();
    }
  }

  std::cout <<"\nReversed strings: \n";
  for (auto &s : result_strs) {
    std::cout << s.get() << "\n";
  }

  return 0;
}

std::string SimpleReverseString(std::string s) {
  char c;
  int size = s.size();
  int half_size = size / 2;

  for (int i = 0; i < half_size; i++) {
    c = s[i];
    s[i] = s[size - i - 1];
    s[size - i - 1] = c;
  }
  return s;
}

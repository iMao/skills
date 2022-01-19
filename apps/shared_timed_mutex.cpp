/**
 * C++14 feature: std::shared_timed_mutex
 */

#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <shared_mutex>
#include <string>
#include <thread>

constexpr int N{100};

void ReverseString(std::string& str) {
  for (int i = 0, j = str.size() - 1; i < str.size() / 2; i++, j--) {
    std::swap(str[i], str[j]);
  }
}

int main() {
  std::string str{"Hello shared_timed_mutex!"};

  std::shared_timed_mutex mut;

  std::thread owner_thread([&]() {
    int i = 0;
    while (i < N) {
      {
        std::unique_lock<std::shared_timed_mutex> ul(mut);
        ReverseString(str);
        std::cout << "owner: ---" << str << "---" << std::endl;
      }
      i++;
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  });

  std::thread reader_0([&]() {
    int i = 0;
    while (i < N) {
      std::shared_lock<std::shared_timed_mutex> sl(mut);
      std::cout << "reader_0: ---" << str << "---" << std::endl;
      i++;
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  });

  std::thread reader_1([&]() {
    int i = 0;
    while (i < N) {
      std::shared_lock<std::shared_timed_mutex> sl(mut);
      std::cout << "reader_1: ---" << str << "---" << std::endl;
      i++;
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  });

  if (owner_thread.joinable()) {
    owner_thread.join();
  }

  if (reader_0.joinable()) {
    reader_0.join();
  }

  if (reader_1.joinable()) {
    reader_1.join();
  }

  return 0;
}

#include "src/system/rwlock.h"

#include <iostream>
#include <thread>

class ThreadSafeCounter {
 public:
  ThreadSafeCounter() { std::cout << "ThreadSafeCounter" << std::endl; }

  // Multiple threads/readers can read the counter's value at the same time.
  unsigned int get() const {
    testlab::RWlockGuard rwlock_guard(rwmutex_,
                                      testlab::RWlockGuard::kSharedLock);
    return value_;
  }

  // Only one thread/writer can increment/write the counter's value.
  void increment() {
    testlab::RWlockGuard rwlock_guard(rwmutex_,
                                      testlab::RWlockGuard::kExclusiveLock);
    value_++;
  }

  // Only one thread/writer can reset/write the counter's value.
  void reset() {
    testlab::RWlockGuard rwlock_guard(rwmutex_,
                                      testlab::RWlockGuard::kExclusiveLock);
    value_ = 0;
  }

 private:
  mutable testlab::RWlock rwmutex_;
  unsigned int value_ = 0;
};

int main() {
  ThreadSafeCounter counter;

  auto increment_and_print = [&counter]() {
    for (int i = 0; i < 3; i++) {
      counter.increment();
      std::cout << std::this_thread::get_id() << ' ' << counter.get() << '\n';

      // Note: Writing to std::cout actually needs to be synchronized as well
      // by another std::mutex. This has been omitted to keep the example small.
    }
  };

  std::thread thread1(increment_and_print);
  std::thread thread2(increment_and_print);
  std::thread thread3(increment_and_print);
  std::thread thread4(increment_and_print);

  thread1.join();
  thread2.join();
  thread3.join();
  thread4.join();

  return 0;
}

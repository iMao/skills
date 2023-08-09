#ifndef SRC_CPP11_MULTITHREADING_TOOLS_H_
#define SRC_CPP11_MULTITHREADING_TOOLS_H_

#include <stdint.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <ctime>
#include <exception>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <random>
#include <ratio>
#include <string>
#include <thread>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::vector;

//класс функтор для запуска в отдельном потоке
class background_task {
public:
  background_task() : a(5) {}
  background_task(int a_) : a(a_) {}
  ~background_task() {}

  void operator()() {
    for (int i = 0; i < a; i++)
      std::cout << "background task is working" << std::endl;
  }

private:
  int a;
};

//класс для безопасного завершения потока
class thread_guard {
public:
  thread_guard() = delete;
  thread_guard(std::thread &t_) : t(t_) {}
  thread_guard(thread_guard const &t) = delete;
  thread_guard(thread_guard &&t) = delete;

  thread_guard &operator=(thread_guard const &t) = delete;
  thread_guard &operator=(thread_guard &&t) = delete;

  ~thread_guard() {
    if (t.joinable()) {
      std::thread::id id = t.get_id();
      t.join();
      std::cout << "thread with id:" << id << " safety joined" << std::endl;
    }
  }

private:
  std::thread &t;
};

//класс функции-члены которого будут передаваться в потоки
class Xth {
public:
  Xth() : a_(2) {}
  Xth(int a) : a_(a) {}
  ~Xth() { std::cout << "\nXth destructor has been called\n"; }
  void do_some_thing(const std::string &str) {
    for (int i = 0; i < a_; i++)
      std::cout << "class Xth{} " << str << std::endl;
  }

  void clear(int &a, int &b, int &c) {
    a = 0;
    b = 0;
    c = 0;
  }

private:
  int a_;
};

enum week { mon, tued, wen };

class Xincrementator {
public:
  Xincrementator() : a_(2) {}
  Xincrementator(int a) : a_(a) {}
  ~Xincrementator() = default;

  void increment_2(int &a, int &b, int &c) {
    for (int i = 0; i < a_; i++) {
      a += 2;
      b += 2;
      c += 2;
    }
  }

private:
  int a_;
};

//------------------------------------------------------------------------------
//первый тест: разные варианты создания потока std::thread
//------------------------------------------------------------------------------
void test_number_1();

//------------------------------------------------------------------------------
//второй тест (передача параметров для функции потока)
//------------------------------------------------------------------------------
void test_number_2();

//------------------------------------------------------------------------------
// третий тест тестирование семантики перемещения для объектов std::thread
//------------------------------------------------------------------------------
void test_number_3();

//------------------------------------------------------------------------------
//тестирование интеллектуальных указателей shared_ptr<>
//------------------------------------------------------------------------------

void TestSharedPtr();

void TestIntelPtrs();

void TestIntelPtrsHard();

//------------------------------------------------------------------------------
//тестирование уникальных указателей unique_ptr<>
//------------------------------------------------------------------------------
class ArrayDeleter {
public:
  void operator()(int *p) {
    std::cout << "\nArrayDeleter():  deleted array \n";
    delete[] p;
  }
};

void TestUniquePtrs();

//------------------------------------------------------------------------------
//тестирование идентификации потоков
//------------------------------------------------------------------------------
class ThreadJoiner {
public:
  void operator()(std::thread &t) {
    if (t.joinable()) {
      cout << "\nThread with id: " << t.get_id() << " will joined" << endl;
      t.join();
    }
  }
};

void test_threads_id();

//------------------------------------------------------------------------------
//тестирование мьютексов
//------------------------------------------------------------------------------
void test_mutex();

// unique_lock()
void test_unique_lock();

//------------------------------------------------------------------------------
//тестиование condition  variables
//------------------------------------------------------------------------------
void insertValue(int &val, std::queue<int> &qu, std::mutex &mut,
                 std::condition_variable &cv);

void getValue(std::queue<int> &qu, std::mutex &mut,
              std::condition_variable &cv);

void test_condition_variables();

void test_condition_variable_queue();

//-----------------------------------------------------------------------------
//тестирование объектов будущих результатов std::future<>
// и асинхронного выполнения функций std::async()
//-----------------------------------------------------------------------------
void AsyncFunction();

void FillArray(std::vector<int> &vec, int size, int init_random_number);

//функция для оборачивания строки
std::string StringBack(std::string s);

class Xc {
private:
public:
  Xc() {}
  ~Xc() {}

  void PrintS(std::string s) { std::cout << s; }

  void operator()(std::string s) { std::cout << s; }
};

void TestAsyncAndFuture();

void TestFutureAndAsync();

//------------------------------------------------------------------------------
//тестирование упакованных задач
//------------------------------------------------------------------------------
double computeMul(double x, double y);

void test_packaged_task();

//------------------------------------------------------------------------------
//тестирование размеров указателей
//------------------------------------------------------------------------------
void test_pointers_size();

//-----------------------------------------------------------------------------
//тестирование библиотеки хроно
//-----------------------------------------------------------------------------
template <typename V, typename R>
std::ostream &operator<<(std::ostream &s,
                         const std::chrono::duration<V, R> &d) {
  s << "[" << d.count() << " of " << R::num << "/" << R::den << "]";
  return s;
}

template <typename C> void PrintClockData() {
  using namespace std;

  std::cout << " -precision: ";

  typedef typename C::period P;

  if (ratio_less_equal<P, milli>::value) {
    typedef typename ratio_multiply<P, kilo>::type TT;
    cout << fixed << double(TT::num) / TT::den << " milliseconds" << endl;
  } else {
    cout << fixed << double(P::num) / P::den << " seconds" << endl;
  }

  cout << "-is steady: " << boolalpha << C::is_steady << endl;
}

std::string TimeAsString(std::chrono::system_clock::time_point &tp);

void TestChronoLibrary();

//------------------------------------------------------------------------------
//тестирование атомарных операций
//------------------------------------------------------------------------------

template <typename atom_t> void get_atomic_info(std::atomic<atom_t> &atom_var) {
  cout << "atomic variable information: " << endl;
  cout << "is_lock_free(): " << std::boolalpha << atom_var.is_lock_free()
       << endl;
  cout << "atomic value:   " << static_cast<atom_t>(atom_var.load()) << endl;
  cout << endl;
}

struct data_Ty {
  int a;
  int b;
  float f;
  string s;

  friend std::ostream &operator<<(std::ostream &os, data_Ty &dty) {
    return os << "a = " << dty.a << " b = " << dty.b << " f = " << dty.f
              << " s = " << dty.s << endl;
  }
};

void test_atomic();

#endif

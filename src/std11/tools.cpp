
#include "tools.h"
#include <cstring>
#include <pthread.h>

//функция для простого потока
void thfunc() {
  std::initializer_list<int> ini{2, 4, 5, 6, 7, 8, 9};

  for (auto x : ini)
    std::cout << "x = " << x << std::endl;
}

void thf(int a) {
  for (int i = 0; i < a; i++)
    std::cout << "Hello from second thread" << std::endl;
}

//работа с потоками по новому стандарту С++17
void test_number_1() {
  //создание простого потока
  std::cout << std::endl;
  std::thread t1(thfunc);
  t1.join();

  //создание потока и передача параметров в функцию потока
  std::cout << std::endl;
  std::thread t2(thf, 2);
  t2.join();

  //создание потока и передача ему объекта-функтора
  std::cout << std::endl;
  std::thread t3((background_task())); //первый способ передачи объекта-функтора
                                       //в дополнительных скобках
  t3.join();

  std::cout << std::endl;
  std::thread t4{background_task(
      1)}; //второй способ передачи объекта-функтора в фигурных {} скобках
  t4.join();

  //создание потока и передача ему лямбда выражения
  std::cout << std::endl;
  auto lambda = [](int a) { std::cout << "a = " << a << std::endl; };

  std::thread t5(lambda, 3);
  t5.join();

  //тестирование безопасного завершения потока
  std::cout << std::endl;
  std::thread t6{background_task()};
  // t6.join();
  thread_guard tg(t6);

  //тестирование безопасного завершения потока при возникновении исключительной
  //ситуации
  std::cout << std::endl;
  auto l = [](int a) {
    try {
      if (a == 0)
        throw std::runtime_error("a = 0 !!!");

      std::cout << "1/a = " << static_cast<double>(1.0 / static_cast<double>(a))
                << std::endl;
    } catch (std::exception &e) {
      std::cout << "EXCEPTION " << e.what() << std::endl;
    }
  };

  std::thread t7(l, 0);
  // t7.join();
  thread_guard tguard(t7);

  //создание потока и передача ему функции-члена класса
  std::cout << std::endl;
  Xth x(3);
  std::thread t8(&Xth::do_some_thing, &x, std::string("xxxx----xxxx"));
  t8.join();
}

//------------------------------------------------------------------------------
//второй тест (передача параметров для функции потока)
//------------------------------------------------------------------------------
void tst_param(int a, float &b, std::string &str, std::string &buf) {
  std::cout << "data inserted into thread\n";
  std::cout << "a = " << a << " b = " << b << " str = " << str
            << " buf = " << buf << std::endl;

  a = 4;

  b = 2.71f;

  str.clear();
  str.append("900");

  buf.clear();
  buf.append("900");

  std::cout << "\ndata changed from thread\n";
  std::cout << "a = " << a << " b = " << b << " str = " << str
            << " buf = " << buf << std::endl;
}

constexpr int BUFFER_SIZE{256};

void test_number_2() {

  //передача параметров функции потока: по значению, по ссылке
  int a{9};
  float b{3.14f};
  char buffer[BUFFER_SIZE];

  memset(buffer, '\0', BUFFER_SIZE);

  sprintf(buffer, "%i", BUFFER_SIZE);

  std::string stbuff("345");
  std::string str(buffer);

  std::thread t1(tst_param, a, std::ref(b), std::ref(stbuff), std::ref(str));
  t1.join();

  std::cout << '\n';
  std::cout << "data from main thread\n";
  std::cout << "a = " << a << " b = " << b << " str = " << stbuff
            << " buf = " << str << std::endl;

  //передача параметров в функцию-член класса
  int A = 7;
  int B = 8;
  int C = 9;
  std::cout << "\nData before thread A = " << A << " B = " << B << " C = " << C
            << std::endl;

  Xth x(2);

  std::thread t2(&Xth::clear, &x, std::ref(A), std::ref(B), std::ref(C));
  t2.join();

  std::cout << "\nData after thread A = " << A << " B = " << B << " C = " << C
            << std::endl;

  A = 1;
  B = 1;
  C = 1;

  std::cout << "\nData before increment A = " << A << " B = " << B
            << " C = " << C << std::endl;

  Xincrementator y(3);
  std::thread t3(&Xincrementator::increment_2, &y, std::ref(A), std::ref(B),
                 std::ref(C));
  t3.join();

  std::cout << "\nData after thread A = " << A << " B = " << B << " C = " << C
            << std::endl;
}

//------------------------------------------------------------------------------
//тестирование семантики перемещения для объектов std::thread
//------------------------------------------------------------------------------

//функция потока задет потоку имя и печатает его имя и id потока
void init_thread(const char *thread_name) {
  char thread_name_buffer[BUFFER_SIZE];

  pthread_setname_np(pthread_self(), thread_name);
  pthread_getname_np(pthread_self(), thread_name_buffer, BUFFER_SIZE);

  if (!strcmp("first thread t1", thread_name_buffer)) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  std::cout << "std::thread::id " << std::this_thread::get_id()
            << " thread name: " << thread_name_buffer << std::endl;
}

void test_number_3() {
  //поддержка семантики перемещения для объектов std::thread
  std::thread t1(init_thread, "first thread t1");
  std::thread t2;
  std::thread t3(init_thread, "third thread t3");

  t2 = std::move(t1);

  t1 = std::thread(init_thread, "new thread t1");

  if (t3.joinable())
    t3.join();

  if (t2.joinable())
    t2.join();

  if (t1.joinable())
    t1.join();
}

//------------------------------------------------------------------------------
//тестирование интеллектуальных указателей
//------------------------------------------------------------------------------
void PrintIntArray(std::shared_ptr<int> &shptr, int size) {

  int i = 0;
  while (i < size) {
    std::cout << shptr.get()[i] << " ";
    i++;
  }
  std::cout << std::endl;
}

void PrintIntArray(int *p, int size) {
  for (int i = 0; i < size; i++) {
    std::cout << p[i] << " ";
  }
  std::cout << '\n';
}

//функция для простого удаления массива
void deleter(int *p) {
  std::cout << "\nfunction deleter() ";
  delete[] p;
}

//функтор для простого удаления массива
class Deleter {
public:
  void operator()(int *p) {
    std::cout << "\nfunctor Deleter()  ";
    delete[] p;
  }
};

//------------------------------------------------------------------------------
//простой тест shared_ptr<int>  разными функциями удаления:
//------------------------------------------------------------------------------
void TestSharedPtr() {
  std::string str{"Hello Shared pointers"};

  // default deleter: delete p;
  std::shared_ptr<Xth> pobject(new Xth(5));
  pobject->do_some_thing(str);

  // deleter - лямбда выражение
  int size = 10;
  std::shared_ptr<int> ptr_array0(new int[size], [](int *p) {
    std::cout << "\nlambda deleter     ";
    delete[] p;
  });

  // deleter - функция
  std::shared_ptr<int> ptr_array1(new int[size], deleter);

  // deleter - функтор
  std::shared_ptr<int> ptr_array2(new int[size], Deleter());

  for (int i = 0; i < size; i++) {
    ptr_array0.get()[i] = (10 - i);
    ptr_array1.get()[i] = (100 - i);
    ptr_array2.get()[i] = (i - 15);
  }

  PrintIntArray(ptr_array0, size);
  PrintIntArray(ptr_array1, size);
  PrintIntArray(ptr_array2, size);

  // deleters будут вызываться в обратном порядке

  std::cout << std::endl;
}

//------------------------------------------------------------------------------
// Более сложная работа с разделяемыми указателями
//------------------------------------------------------------------------------
void TestIntelPtrs() {

  //простые shared_ptr указатели
  std::shared_ptr<std::string> ptr_nica(new std::string("nica"));
  std::shared_ptr<std::string> ptr_jutta(new std::string("jutta"));
  std::shared_ptr<std::string> ptr_nico{new std::string("nico")};

  std::cout << "ptr_nica ->" << (*ptr_nica) << std::endl;
  std::cout << "ptr_jutta->" << (*ptr_jutta) << std::endl;
  std::cout << "ptr_nico ->" << (*ptr_nico) << std::endl;

  (*ptr_nica)[0] = 'N';
  ptr_jutta->replace(0, 1, "J");
  ptr_nico->append("-hero");

  std::cout << '\n';
  std::cout << "ptr_nica ->" << (*ptr_nica) << std::endl;
  std::cout << "ptr_jutta->" << (*ptr_jutta) << std::endl;
  std::cout << "ptr_nico ->" << (*ptr_nico) << std::endl;

  std::cout << '\n';
  std::cout << "Nica  use count = " << ptr_nica.use_count() << std::endl;
  std::cout << "Jutta use count = " << ptr_jutta.use_count() << std::endl;
  std::cout << "Nico  use count = " << ptr_nico.use_count() << std::endl;

  std::vector<std::shared_ptr<std::string>> vec;

  vec.push_back(ptr_nica);
  vec.push_back(ptr_nica);

  vec.push_back(ptr_jutta);
  vec.push_back(ptr_jutta);
  vec.push_back(ptr_jutta);
  vec.push_back(ptr_jutta);

  vec.push_back(ptr_nico);
  vec.push_back(ptr_nico);
  vec.push_back(ptr_nico);

  std::cout << '\n';
  std::cout << "Nica  use count = " << ptr_nica.use_count() << std::endl;
  std::cout << "Jutta use count = " << ptr_jutta.use_count() << std::endl;
  std::cout << "Nico  use count = " << ptr_nico.use_count() << std::endl;

  std::shared_ptr<std::string> nico_;
  nico_.reset(new std::string("nico-pico"));

  std::cout << '\n';
  std::cout << "nico_ ->" << (*nico_) << std::endl;
  std::cout << "nico_ use count " << nico_.use_count() << std::endl;

  vec.clear();

  std::cout << '\n';
  std::cout << "std::vector<std::shared_ptr<std::string>> cleared\n";
  std::cout << "Nica  use count = " << ptr_nica.use_count() << std::endl;
  std::cout << "Jutta use count = " << ptr_jutta.use_count() << std::endl;
  std::cout << "Nico  use count = " << ptr_nico.use_count() << std::endl;

  ptr_nica = nullptr;
  ptr_jutta = nullptr;
  ptr_nico = nullptr;
  nico_ = nullptr;

  std::cout << '\n';
  std::cout << "shared_ptrs = nullptr\n";
  std::cout << "Nica  use count = " << ptr_nica.use_count() << std::endl;
  std::cout << "Jutta use count = " << ptr_jutta.use_count() << std::endl;
  std::cout << "Nico  use count = " << ptr_nico.use_count() << std::endl;
  std::cout << "nico_ use count = " << nico_.use_count() << std::endl;
}

class SuperData {
private:
  int *a;
  int b;
  int c;

public:
  SuperData() {
    a = new int;
    *a = 10;
    b = 2;
    c = (*a) / b;
  };

  ~SuperData() {
    if (a != nullptr) {
      delete a;
    }
    b = 0;
    c = 0;
    std::cout << "All SuperData resources was returned\n";
  }

  void Print() {
    std::cout << "a: " << *a << " b: " << b << " c: " << c << std::endl;
  }
};

//функтор для реализации стратегии закрытия и удаления файла
class FileDeleter {
private:
  std::string filename_;

public:
  FileDeleter() = delete;
  FileDeleter(std::string const &filename) : filename_(filename) {}
  ~FileDeleter() = default;
  void operator()(std::ofstream *ptr_ofstream) {
    delete ptr_ofstream;
    std::remove(filename_.c_str());
    std::cout << "file " << filename_ << " was removed \n";
  }
};

//------------------------------------------------------------------------------
//более сложное использование shared_ptr указателей со своей стратегией удаления
//------------------------------------------------------------------------------
void TestIntelPtrsHard() {
  std::shared_ptr<std::string> pstr(
      new std::string("Hello"), [](std::string *p) {
        std::cout << "\nYou deleted string: " << (*p) << std::endl;
        delete p;
      });

  std::cout << "\npstr: " << (*pstr) << std::endl;
  pstr = nullptr;

  std::shared_ptr<int> ptr_array(new int[10], [](int *p) {
    std::cout << "\nYou deleted array: ";
    PrintIntArray(p, 10);
    delete[] p;
  });

  for (int i = 0; i < 10; i++) {
    ptr_array.get()[i] = i;
  }

  std::cout << "Array was initialiazed \n";
  std::cout << "Array has values   ";

  PrintIntArray(ptr_array, 10);

  ptr_array = nullptr;

  std::cout << std::endl
            << "ptr_array.use_count() = " << ptr_array.use_count() << std::endl;

  std::shared_ptr<SuperData> super_data_ptr(
      new SuperData(), [](SuperData *spd) {
        std::cout << "\nremoving SuperData ptr\n";
        delete spd;
      });

  super_data_ptr->Print();

  super_data_ptr = nullptr;

  //интеллектуальный указатель на ресурс связанный с файлом
  std::shared_ptr<std::ofstream> fp(new std::ofstream("tmpfile.txt"),
                                    FileDeleter("tmpfile.txt"));

  (*fp) << "this is test information\n";

  fp = nullptr;

  std::shared_ptr<int> shptr(new int[5], std::default_delete<int[]>());
  shptr.get()[0] = 10;
  shptr.get()[1] = 12;
  shptr.get()[2] = 15;

  std::cout << std::endl;
  std::cout << "[0]: " << shptr.get()[0] << " [1]: " << shptr.get()[1]
            << " [2]: " << shptr.get()[2] << std::endl;
}

//------------------------------------------------------------------------------
//тестирование уникальных указателей unique_ptr<>
//------------------------------------------------------------------------------
//функция исток
std::unique_ptr<std::string> CreateString(char const *charArray) {
  return std::unique_ptr<std::string>(new std::string(charArray));
}

//функция сток
void PrintString(std::unique_ptr<std::string> ps) {
  std::cout << "\nYour string: " + (*ps) << std::endl;
}

void Fdeleter(int *p) {
  std::cout << "\nYou will delete array with function \'fdeleter\' "
            << std::endl;
  delete[] p;
}

void TestUniquePtrs() {
  //тестирование базовых возможностей уникальных указателей
  std::unique_ptr<std::string> pStr(new std::string("uma"));

  (*pStr)[0] = 'U';
  std::cout << "\nString: " << *pStr << std::endl;

  pStr->append("-puma");
  std::cout << "\nString: " << *pStr << std::endl;

  (*pStr)[2] = 'A';
  std::cout << "\nString: " << *pStr << std::endl;

  pStr = nullptr;

  //указатель на массив строк
  std::unique_ptr<std::string[]> text(new std::string[5]);

  text[0] = std::string("Hello");
  text[1] = std::string("unique_ptr<>");
  text[2] = std::string(" it is cool");
  text[3] = std::string("very cool and fun");
  text[4] = std::string("OK");

  std::cout << '\n';

  for (int i = 0; i < 5; i++) {
    std::cout << text[i] << " ";
  }

  text = nullptr;

  // указатель на массив чисел с указанием собственного удалителя
  std::unique_ptr<int[], void (*)(int *)> up(new int[10], [](int *p) {
    std::cout << "\narray int[] was deleted: ";
    for (int i = 0; i < 10; i++) {
      std::cout << p[i] << " ";
    }
    std::cout << std::endl;
    delete[] p;
  });

  for (int i = 0; i < 10; i++) {
    up[i] = i;
  }

  up = nullptr;

  //указатель на массив строк со своим удалителем
  std::unique_ptr<std::string[], void (*)(std::string *)> page(
      new std::string[5], [](std::string *p) -> void {
        std::cout << "\nYou will delete a page of text\n";
        delete[] p;
      });

  page[0] = std::string("Hello");
  page[1] = std::string("unique_ptr<>");
  page[2] = std::string(" it is cool");
  page[3] = std::string("very cool and fun");
  page[4] = std::string("OK");

  std::cout << '\n';
  for (int i = 0; i < 5; i++) {
    std::cout << page[i] << " ";
  }

  page = nullptr;

  //потеря владения объектом
  std::unique_ptr<std::string> upStr(new std::string("Object"));

  //вызов функции release() - приводит к потере владения
  //без вызова функции-удалителя
  std::string *str = upStr.release();

  std::cout << "\nstr - " << *str << std::endl;

  if (upStr == nullptr) {
    std::cout << "upStr: nullptr\n";
  }

  delete str;

  //передача владения
  std::unique_ptr<std::string> ps(new std::string("Super Object"));

  upStr = std::move(ps); //передача владения std::move()

  std::cout << '\n';
  std::cout << "unique_ptr<string> upStr has - " << *upStr << std::endl;

  upStr = nullptr;

  if (ps)
    std::cout << "\nps is owner of object\n";
  else
    std::cout << "\nps is not owner of object\n";

  ps = nullptr;

  //передача владения 2
  std::unique_ptr<int, void (*)(int *)> up1(new int, [](int *p) {
    std::cout << "\ndeleted up1\n";
    delete p;
  });
  *up1 = 2;

  std::unique_ptr<int, void (*)(int *)> up2(new int, [](int *p) {
    std::cout << "\ndeleted up2\n";
    delete p;
  });
  *up2 = 4;

  up2 = std::move(up1); //для потерянного объекта связанного с up2 - будет
                        //вызвана функция удаления

  std::cout << "\nup2 -> " << *up2 << std::endl;

  //пустому unique_ptr<> присваиваем новое значение
  up1 =
      std::unique_ptr<int, void (*)(int *)>(new int, [](int *p) { delete p; });
  *up1 = 10;
  std::cout << "\nup1 -> " << *up1 << std::endl;

  //исток и сток для unique_ptr<>
  std::unique_ptr<std::string> p = CreateString("America");

  PrintString(std::move(p));

  //операторы удаления
  std::unique_ptr<int[], void (*)(int *)> up3(new int[4], [](int *p) -> void {
    std::cout << "\ndeclaration void(*)(int*)\n";
    delete[] p;
  });

  std::unique_ptr<int[], std::function<void(int *)>> up4(
      new int[10], [](int *p) {
        std::cout << "\ndeclaration std::function<void(int*)> \n";
        delete[] p;
      });

  std::function<bool(int *)> smart_deleter = [](int *p) -> bool {
    if (!p) {
      std::cout << "\npointer: nullptr\n";
      return false;
    }
    std::cout << "\nsmart_deleter worked\n";
    delete[] p;
    return true;
  };

  std::unique_ptr<int[], decltype(smart_deleter)> upsmart(new int[10],
                                                          smart_deleter);

  auto l = [](int *p) {
    std::cout << "\ndeclaration decltype(l)\n";
    delete[] p;
  };

  std::unique_ptr<int[], decltype(l)> up5(new int[8], l);

  std::unique_ptr<int[], std::function<void(int *)>> up7(new int[10], Fdeleter);

  std::unique_ptr<int[], decltype(ArrayDeleter())> up8(new int[2],
                                                       ArrayDeleter());
}

//------------------------------------------------------------------------------
//тестирование идентификации потоков
//------------------------------------------------------------------------------
void some_work() {
  std::thread::id id = std::this_thread::get_id();
  cout << "\nThread id: " << id << endl;
}

void test_threads_id() {

  //получим id текущего потока
  std::thread::id this_thread_id = std::this_thread::get_id();

  //получаем сколько потоков возможно по настоящему
  int number_threads = std::thread::hardware_concurrency();

  cout << "\nSystem has hardware concurrency: " << number_threads << endl;
  cout << "\nThis thread id: " << this_thread_id << endl;

  //резервируем размер вектора для потоков
  std::vector<std::thread> pool_threads(number_threads);
  for (int j = 0; j < number_threads; j++) {
    pool_threads.emplace_back(some_work);
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  //поочередный вызов join() для каждого потока
  std::for_each(pool_threads.begin(), pool_threads.end(), ThreadJoiner());

  pool_threads.clear();
}

//------------------------------------------------------------------------------
//тестирование мьютексов
//------------------------------------------------------------------------------
void print_rec(const string &s, std::recursive_mutex &mut) {
  {
    std::lock_guard<std::recursive_mutex> lguard(mut);

    for (char c : s)
      cout.put(c);

    cout << endl;
  }
}

void print(const string &s, std::mutex &mut) {
  {
    std::lock_guard<std::mutex> lguard(mut);

    for (char c : s)
      cout.put(c);

    cout << endl;
  }
}

void ReverseString(string &str, std::recursive_mutex &rec_mutex) {
  {
    std::lock_guard<std::recursive_mutex> lg(rec_mutex);

    string copy_str(str);
    str.clear();

    for (auto i = copy_str.rbegin(); i != copy_str.rend(); ++i) {
      string ch{*i};
      str.append(ch);
    }
    print_rec(str, rec_mutex);
  }
}

int SomeWorkWhileMutexBusy() {
  static int i = 0;
  i++;
  return i;
}

void swap(int &a, int &b) {
  a = a + b;
  b = a - b;
  a = a - b;
}

void test_mutex() {
  //использование простого мьютекса
  std::mutex mut;

  string strhello("Hello mutex");
  string strgoodday("Good day");
  string strgoodmorning("Good morning");

  std::thread t1(print, std::ref(strhello), std::ref(mut));
  std::thread t2(print, std::ref(strgoodday), std::ref(mut));

  print(strgoodmorning, mut);

  t1.join();
  t2.join();

  cout << endl;

  //использование рекурсивных мьютексов (3 потока конкурируют за доступ к строке
  //и за доступ в консоль)
  std::recursive_mutex rec_mutex;

  std::thread t3(ReverseString, std::ref(strhello), std::ref(rec_mutex));
  std::thread t4(ReverseString, std::ref(strhello), std::ref(rec_mutex));
  std::thread t5(ReverseString, std::ref(strhello), std::ref(rec_mutex));

  t3.join();
  t4.join();
  t5.join();

  cout << endl;

  //тестирование попытки блокировки
  std::mutex try_mutex;

  std::thread t6([&]() {
    {
      std::lock_guard<std::mutex> lgd(try_mutex);
      for (int i = 0; i < 500; i++) {
        cout << "*";
      }
    }
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(1));

  int counter = 0;
  while (try_mutex.try_lock() == false) {
    counter = SomeWorkWhileMutexBusy();
  }

  {
    std::lock_guard<std::mutex> lockgrd(try_mutex, std::adopt_lock);
    cout << endl;
    cout << "counter =  " << counter << endl;
  }

  t6.join();

  //тестирование std::timed_mutex  и std::recursive_timed_mutex
  std::timed_mutex t_mutex;

  //поток будет работать 3 секунды и блокировать мьютекс
  std::thread t7([&]() {
    {
      std::lock_guard<std::timed_mutex> tlg(t_mutex);
      for (int i = 0; i < 3; i++) {
        cout << "thread t7 pause 1 sec" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); //пауза в 1 sec
      }
    }
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  //будем пытаться захватить мьютекс 4 сек
  if (t_mutex.try_lock_for(std::chrono::seconds(4))) {
    {
      std::lock_guard<std::timed_mutex> tlguard(t_mutex, std::adopt_lock);
      cout << endl;
      cout << "timeout end" << endl;
    }
  } else {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout << endl;
    cout << "mutex is busy more then " << 4 << " sec" << endl;
  }

  t7.join();

  //работа с несколькими блокировками
  cout << endl;
  cout << "Test multiple mutex blocking" << endl;

  std::mutex mut1;
  std::mutex mut2;
  std::mutex mut3;

  int val_1{10};
  int val_2{5};

  auto lambda_swap = [&]() {
    {
      //будет содержать индекс первой неудачной блокировки
      int index_failure_lock = 0;
      //попытка блокировки трех мьютексов
      index_failure_lock = std::try_lock(mut1, mut2, mut3);

      // std::lock(mut1, mut2, mut3);
      // запрос на блокировку трех мьютексов
      if (index_failure_lock < 0) {
        std::lock_guard<std::mutex> lgdMut1(mut1, std::adopt_lock);
        std::lock_guard<std::mutex> lgdMut2(mut2, std::adopt_lock);
        std::lock_guard<std::mutex> lgdMut3(mut3, std::adopt_lock);

        cout << endl << "thread id: " << std::this_thread::get_id() << endl;
        cout << "before swaping  val_1: " << val_1 << " val_2: " << val_2
             << endl;

        swap(val_1, val_2);

        cout << "After swaping   val_1: " << val_1 << " val_2: " << val_2
             << endl;
      } else {
        std::lock_guard<std::mutex> lgdMut3(mut3);
        cout << endl
             << "thread id: " << std::this_thread::get_id()
             << "  cannot block mutex with index: " << index_failure_lock
             << endl;
      }
    }
  };

  std::thread t8(lambda_swap);
  std::thread t9(lambda_swap);
  std::thread t10(lambda_swap);

  t8.join();
  t9.join();
  t10.join();
}

// unique_lock()
void test_unique_lock() {
  std::mutex mut;

  string s("shared string");

  //создали защиту для мьютекса но не заблокировали
  std::thread t1([&]() {
    std::unique_lock<std::mutex> l(mut, std::defer_lock);

    l.lock();
    s.append("_t1");
    cout << endl << "thread t1 our string is: " << s << endl;
    l.unlock();
  });

  //создали защиту для мьютекса но не заблокировали
  std::thread t2([&]() {
    std::unique_lock<std::mutex> l(mut, std::defer_lock);

    l.lock(); //блокировка
    s.append("_t2");
    cout << endl << "thread t2 our string is: " << s << endl;
    l.unlock(); //разблокировка
  });

  std::thread t3([&]() {
    {
      //попытка заблокировать мьютекс
      std::unique_lock<std::mutex> ul(mut, std::try_to_lock);
      if (ul) {
        s.append("_t3");
        cout << endl << "thread t3 our string is: " << s << endl;
      } else
        cout << endl << "t3 can not lock mutex " << endl;
    }
  });

  {
    //создали защиту для мьютекса и сразу же заблокировали его
    std::unique_lock<std::mutex> lock(mut);
    s.append("_main_thread_");
    cout << endl << "our string is: " << s << endl;
  }

  t1.join();
  t2.join();
  t3.join();
}

//------------------------------------------------------------------------------
//тестирование condition  variables
//------------------------------------------------------------------------------
void InsertValue(int &val, std::queue<int> &qu, std::mutex &mut,
                 std::condition_variable &cv) {
  for (int i = 0; i < 10; i++) {
    {
      std::lock_guard<std::mutex> l(mut);
      qu.push(val);
      val++;
    }
    cv.notify_one();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void GetValue(std::queue<int> &qu, std::mutex &mut,
              std::condition_variable &cv) {
  for (int i = 0; i < 10; i++) {
    std::unique_lock<std::mutex> ul(mut);
    cv.wait(ul, [&]() -> bool { return !qu.empty(); });
    cout << "val: " << qu.front() << " queue size: " << qu.size() << endl;
    qu.pop();
  }
}

void TestConditionVariables() {
  //простое тестирование условных переменных
  std::condition_variable condVar;
  std::mutex mut;

  bool ready = true;
  string s("0");

  std::thread t1([&]() {
    for (int i = 0; i < 10; i++) {
      {
        std::lock_guard<std::mutex> ul(mut);
        s.append("-");
        cout << s << endl;
        ready = true;
      }
      condVar.notify_one();
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
  });

  std::thread t2([&]() {
    for (int i = 0; i < 10; i++) {
      std::unique_lock<std::mutex> ul(mut);
      condVar.wait(ul, [&]() -> bool { return ready; });
      s.append("0");
      cout << s << endl;
      ready = false;
      // std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  });

  t1.join();
  t2.join();
}

//более сложный пример с очередью значений std::queue<int> qu
void TestConditionVariableQueue() {
  std::queue<int> qu;
  std::condition_variable cond_var;
  std::mutex qmutex;

  int value{0};

  std::thread t3(InsertValue, std::ref(value), std::ref(qu), std::ref(qmutex),
                 std::ref(cond_var));
  std::thread t4(GetValue, std::ref(qu), std::ref(qmutex), std::ref(cond_var));

  t3.join();
  t4.join();
}

//тестирование wait_for()
void TestConditionVariablesQueueWaitFor() {
  cout << endl << "Test condition_variable.wait_for()" << endl;
  std::queue<int> qu;
  std::condition_variable cvar;
  std::mutex some_mutex;
  int queue_length = 10;

  std::thread t5([&]() {
    for (int i = 0; i < queue_length; i++) {
      {
        std::lock_guard<std::mutex> lg(some_mutex);
        qu.push(i);
      }
      cvar.notify_one();
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
  });

  std::thread t6([&]() {
    int counter = 0;
    while (true) {
      std::unique_lock<std::mutex> lock(some_mutex);
      cvar.wait_for(lock, std::chrono::milliseconds(1),
                    [&]() -> bool { return (qu.size() == queue_length); });
      ++counter;
      if (qu.size() < queue_length) {
        std::cout << "counter: " << counter << " early!\n";
      } else {
        cout << "\nqueue is filled";
        cout << "\n";
        while (!qu.empty()) {
          cout << qu.front() << " " << endl;
          qu.pop();
        }
        break;
      }
    }
  });

  t5.join();
  t6.join();
}

//------------------------------------------------------------------------------
//тестирование объектов
//будущих результатов и асинхронного выполнения функций
//------------------------------------------------------------------------------
void AsyncFunction() {
  std::cout << std::endl << "Hello from async thread" << std::endl;
}

void FillArray(std::vector<int> &vec, int size, int init_random_number) {
  std::default_random_engine dre(init_random_number);
  std::uniform_int_distribution<int> id(1, 1000);

  for (int j = 0; j < size; j++) {
    vec.push_back(id(dre));
  }
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

void TestAsyncAndFuture() {
  int N = 10;

  std::future<int> intf = std::async(std::launch::async, [=]() -> int {
    int sum = 0;
    for (int i = 0; i < N; i++) {
      sum += i;
    }
    return sum;
  });

  std::cout << "future<int> intf: " << intf.get() << std::endl;

  std::future<std::string> strf =
      std::async(std::launch::deferred, SimpleReverseString,
                 "Sator Arepo tenet opera rotas");

  std::cout << "\nstd::future<string> strf: " << strf.get() << std::endl;

  Xc x;
  std::future<void> voidf0 =
      std::async(std::launch::deferred, &Xc::PrintS, &x, "function member");

  std::future<void> voidf1 = std::async(std::launch::deferred, Xc(), "123");

  std::cout << "\nvoidf0: ";
  voidf0.get();

  std::cout << "\nvoidf1: ";
  voidf1.get();
  std::cout << std::endl;
}

void TestFutureAndAsync() {
  //простой тест асинхроного выполнеия функциональной сущности
  int sum{0};
  int a{5};
  int b{2};

  std::future<int> f1 = std::async([](int a) -> int { return a * a; }, a);

  std::future<int> f2 = std::async([](int b) -> int { return b * b * b; }, b);

  sum = f1.get() + f2.get();

  std::cout << "\nsum: " << sum << std::endl;

  //отложеный вызов функциональной сущности
  std::future<void> f3 = std::async(std::launch::deferred, AsyncFunction);
  f3.get();

  std::future<double> f4 = std::async(
      std::launch::async, [](double d) -> double { return pow(d, 3); }, 3.0);
  std::cout << "\n3.0^3 = " << f4.get() << std::endl;

  //ожидание будущих результатов, запрос состояния
  std::vector<int> vec;

  std::future<void> f5{
      std::async(std::launch::async, FillArray, std::ref(vec), 1000, 5)};
  std::future_status status = f5.wait_for(std::chrono::microseconds(1));

  if (status == std::future_status::deferred)
    std::cout << std::endl << "status: deferred" << std::endl;

  if (status == std::future_status::ready)
    std::cout << std::endl << "status: ready" << std::endl;

  if (status == std::future_status::timeout)
    std::cout << "status: timeout" << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(2));

  f5.get();

  //разделяемые объекты будущих результатов
  std::mutex mut;

  std::shared_future<int> shf{std::async([&]() -> int {
    int num{0};
    std::cout << "\ninput num: ";
    std::cin >> num;

    if (!std::cin) {
      throw std::runtime_error("number is not valid");
    }

    return num;
  })};

  auto lam = [&]() -> void {
    {
      try {
        std::lock_guard<std::mutex> l(mut);
        std::cout << '\n'
                  << "thread id: " << std::this_thread::get_id()
                  << "  num: " << shf.get() << std::endl;
      } catch (const std::exception &e) {
        std::cerr << std::endl
                  << "EXCEPTION in thread: " << std::this_thread::get_id()
                  << " : " << e.what() << std::endl;
      }
    }
  };

  auto f6{std::async(lam)};
  auto f7{std::async(lam)};
  auto f8{std::async(lam)};
  auto f9{std::async(lam)};

  //ждем завершения потоков
  f6.get();
  f7.get();
  f8.get();
  f9.get();
}

//------------------------------------------------------------------------------
//тестирование упакованных задач
//------------------------------------------------------------------------------
void TestPackagedTask() {
  //упакованная задача (сделанная из функции)
  double x = 2.2, y = 2.0;

  std::packaged_task<double(double, double)> packaged_function(
      ComputeMul<double>);
  std::future<double> fd{packaged_function.get_future()};

  std::thread t1(std::move(packaged_function), x, y);
  t1.join();

  cout << '\n' << "x: " << x << " y: " << y << " x * y = " << fd.get() << endl;

  //упакованная задача (сделанная из лямбда выражения)
  int a{8};
  auto lambda{[&]() -> int { return (a * a); }};
  std::packaged_task<int()> packaged_lambda(lambda);
  std::future<int> fint{packaged_lambda.get_future()};

  std::thread t2(std::move(packaged_lambda));

  cout << endl << "a*a = " << fint.get() << endl;

  t2.join();

  //упакованная задача сделанная из функтора
  std::packaged_task<void(string)> packaged_functor{Xc()};
  std::future<void> fv{packaged_functor.get_future()};

  cout << "\nXc() -> ";
  std::thread t3(std::move(packaged_functor), std::string("Hello Xc"));
  t3.join();

  //упакованная задача сделанная из статической функции члена класса
  std::packaged_task<void(std::string)> packaged_static_function(
      Xc::PrintString);
  std::future<void> fvxc{packaged_static_function.get_future()};

  std::cout << "\npackaged_static_function: ";
  std::thread t4(std::move(packaged_static_function),
                 "static function from class Xc");

  t4.join();
}

//------------------------------------------------------------------------------
//тестирование библиотечки хроно
//------------------------------------------------------------------------------
std::string TimeAsString(std::chrono::system_clock::time_point &tp) {
  time_t t = std::chrono::system_clock::to_time_t(tp);
  std::string ts = std::ctime(&t);
  ts.resize(ts.size() - 1);

  return ts;
}

void TestChronoLibrary() {
  //тестирование интервалов

  //интервал 2 минуты с целым отсчетом
  std::chrono::duration<int, std::ratio<60, 1>> two_minute(2);

  //интервал 0.5 минуты с дробным отсчетом
  std::chrono::duration<double, std::ratio<60>> half_minute(0.5);

  //интервал 100 милисекунд
  std::chrono::duration<int, std::ratio<1, 1000>> millisec_100(100);

  //интервал 5 секунд
  std::chrono::duration<int> five_sec(5);

  //интервал 10 микросекунд
  std::chrono::duration<int, std::ratio<1, 1000000>> microsec_10(10);

  //интервал 10 пикосекунд
  std::chrono::duration<int, std::pico> picosec(10);

  //интервал 2 секунды
  std::chrono::seconds two_seconds(2);

  //интервал 1 минута
  std::chrono::minutes minutes(1);

  //нтервал 100 наносекунд
  std::chrono::nanoseconds nanosec_100(100);

  std::chrono::microseconds d = millisec_100 - microsec_10;
  std::cout << std::endl
            << "d = 100millisec - 10microsec = " << d.count() << " microsec"
            << std::endl;

  std::chrono::seconds s(10);
  s += two_minute + five_sec;
  std::cout << std::endl
            << "s += two_minute + five_sec = " << s.count() << " sec"
            << std::endl;

  auto dur_3_4_max = std::chrono::duration<int, std::ratio<3, 4>>::max();
  std::cout << std::endl << "3/4 max() " << dur_3_4_max.count() << std::endl;

  auto dur_3_4_min = std::chrono::duration<int, std::ratio<3, 4>>::min();
  std::cout << std::endl << "3/4 min() " << dur_3_4_min.count() << std::endl;

  std::cout << std::endl;
  std::cout << two_seconds << std::endl;
  std::cout << millisec_100 << std::endl;
  std::cout << microsec_10 << std::endl;
  std::cout << minutes << std::endl;
  std::cout << nanosec_100 << std::endl;
  std::cout << std::endl;

  // duration_cast<>
  std::chrono::seconds six_two(62);
  std::chrono::minutes m =
      std::chrono::duration_cast<std::chrono::minutes>(six_two);
  std::cout << m << std::endl;

  std::chrono::seconds sec_dur =
      std::chrono::duration_cast<std::chrono::seconds>(half_minute);
  std::cout << sec_dur << std::endl;
  std::cout << std::endl;

  //разложение интервала на часы, минуты, секунды
  std::chrono::milliseconds time_milliseconds(12908234);

  std::chrono::hours h =
      std::chrono::duration_cast<std::chrono::hours>(time_milliseconds);
  std::chrono::minutes m_ = std::chrono::duration_cast<std::chrono::minutes>(
      time_milliseconds % std::chrono::hours(1));
  std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(
      time_milliseconds % std::chrono::minutes(1));
  std::chrono::milliseconds msec =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          time_milliseconds % std::chrono::seconds(1));

  std::cout << "raw " << h << "::" << m_ << "::" << sec << "::" << msec
            << std::endl;
  std::cout << h.count() << "::" << m_.count() << "::" << sec.count()
            << "::" << msec.count() << std::endl;

  //часы в системе
  std::cout << "\nSystem clock: ";
  PrintClockData<std::chrono::system_clock>();

  // std::chrono::system_clock::period

  std::cout << "\nSteady clock: ";
  PrintClockData<std::chrono::steady_clock>();

  std::cout << "\nHigh resolution clock: ";
  PrintClockData<std::chrono::high_resolution_clock>();

  //моменты времени
  std::chrono::time_point<std::chrono::steady_clock> tp_start =
      std::chrono::steady_clock::now();

  std::this_thread::sleep_for(std::chrono::seconds(1));

  std::chrono::time_point<std::chrono::steady_clock> tp_stop =
      std::chrono::steady_clock::now();

  std::cout << "\ndifference time:" << (tp_stop - tp_start).count()
            << std::endl;

  //эпоха часов
  std::chrono::time_point<std::chrono::system_clock> tpsysclk;
  std::cout << "\nepoch:" << TimeAsString(tpsysclk) << std::endl;

  tpsysclk = std::chrono::system_clock::now();
  std::cout << "\nnow:" << TimeAsString(tpsysclk) << std::endl;

  //время с начала эпохи
  auto tp = tpsysclk.time_since_epoch();

  std::chrono::minutes t_minutes =
      std::chrono::duration_cast<std::chrono::minutes>(tp);

  std::cout << "\ntime from epoch started nanosec: " << tp << std::endl;

  std::cout << "\ntime from epoch started minutes: " << t_minutes << std::endl;
}

//------------------------------------------------------------------------------
//тестирование размеров указателей
//------------------------------------------------------------------------------
void TestPointersSize() {
  //проверка размерности указателя
  double s = 9.0;
  double *ptr = &s;

  int a = 9;
  int *intPtr = &a;

  char c{'h'};
  char *pc{&c};

  A *object_ptr;
  B object_b;
  C object_c;
  object_ptr = &object_b;

  cout << endl
       << "sizeof(double*) = " << sizeof(ptr)
       << " sizeof(*double) = " << sizeof(s) << endl;
  cout << endl
       << "sizeof(int*)    = " << sizeof(intPtr)
       << " sizeof(*int) = " << sizeof(a) << endl;
  cout << endl
       << "sizeof(char*)   = " << sizeof(pc) << " sizeof(*char) = " << sizeof(c)
       << endl;
  cout << endl
       << "sizeof(A*)   = " << sizeof(object_ptr)
       << " sizeof(*object_ptr) = " << sizeof(A) << endl;

  cout << endl
       << "sizeof(A*)   = " << sizeof(object_ptr)
       << " sizeof(*object_ptr) = " << sizeof(B) << endl;

  object_ptr = &object_c;
  cout << endl
       << "sizeof(A*)   = " << sizeof(object_ptr)
       << " sizeof(*object_ptr) = " << sizeof(C) << endl;

  DataStruct *data_struct_ptr;
  DataStruct ds{.a = 10, .b = 3.14, .c = 'c'};

  data_struct_ptr = &ds;

  cout << endl
       << "sizeof(DataStruct*)   = " << sizeof(data_struct_ptr)
       << " sizeof(*data_struct_ptr) = " << sizeof(DataStruct) << endl;

  NextDataStruct *next_data_struct_ptr;
  NextDataStruct nds;
  nds.a = 10;
  nds.b = 2.1;
  nds.c = 'h';
  next_data_struct_ptr = &nds;

  cout << endl
       << "sizeof(NextDataStruct*)   = " << sizeof(next_data_struct_ptr)
       << " sizeof(*next_data_struct_ptr) = " << sizeof(NextDataStruct) << endl;
}

//------------------------------------------------------------------------------
//тестирование атомарных операций
//------------------------------------------------------------------------------

std::atomic<bool> bool_data(false);

std::atomic<char> char_data(-4);
std::atomic<unsigned char> uchar_data('F');

std::atomic<short> short_data(-129);
std::atomic<unsigned short> ushort_data(65000);

std::atomic<int> int_data(0);
std::atomic<unsigned int> uint_data(0);

std::atomic<long> long_data(-1000);
std::atomic<unsigned long> ulong_data(0);

std::atomic<long long> llong_data(-1000);
std::atomic<unsigned long long> ullong_data(0);

std::atomic<uint32_t> uint32var;

std::atomic<int *> atomic_ptr;

std::atomic_flag flag(ATOMIC_FLAG_INIT);

void TestAtomic() {
  //получение характеристик атомарных переменных
  std::thread t1([]() {
    get_atomic_info(bool_data);
    get_atomic_info(char_data);
    get_atomic_info(uchar_data);
    get_atomic_info(short_data);
    get_atomic_info(ushort_data);
    get_atomic_info(int_data);
    get_atomic_info(uint_data);
    get_atomic_info(long_data);
    get_atomic_info(ulong_data);
    get_atomic_info(llong_data);
    get_atomic_info(ullong_data);
  });

  if (t1.joinable())
    t1.join();

  //работа с атомарными переменными
  uint_data.store(10); //атомарная инициализация

  std::thread t3([]() {
    while (auto a = uint_data.load()) {
      cout << "atomic unsigned int data: " << a << endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
  });

  std::thread t4([]() {
    for (;;) {
      uint_data.fetch_sub(1);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));

      if (!uint_data.load())
        break;
    }
  });

  if (t3.joinable())
    t3.join();

  if (t4.joinable())
    t4.join();

  //синхронизация доступа к данным на основе std::atomic<bool> bool_data;
  data_Ty dty{2, 3, 5.2, "Hello string"};

  std::thread t5([&]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    dty.a = 7;
    dty.b = 7;
    dty.f = 7.0;
    dty.s = "Thread t5";

    bool_data.store(true);
  });

  std::thread t6([&]() {
    while (!bool_data.load()) {
      cout << "data not ready" << endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    cout << dty << endl;
  });

  t5.join();
  t6.join();

  //демонстрация атомарных операций с атомарными переменными
  std::atomic_init(&uint32var, 100u);
  cout << "std::atomic<uint32_t> uint32var - " << uint32var.load() << endl;

  uint32var.fetch_add(10);
  cout << "std::atomic<uint32_t> uint32var - fetch_add(10)    "
       << uint32var.load() << endl;

  uint32var.fetch_sub(90);
  cout << "std::atomic<uint32_t> uint32var - fetch_sub(90)    "
       << uint32var.load() << endl;

  uint32var.store(50);
  cout << "std::atomic<uint32_t> uint32var - store(50)        "
       << uint32var.load() << endl;

  cout << "std::atomic<uint32_t> uint32var - exchange(0x5555) "
       << uint32var.exchange(0x5555) << endl;
  cout << "new value -  " << uint32var.load() << endl;

  uint32var.fetch_and(0xFFFF);
  cout << "std::atomic<uint32_t> uint32var - fetch_and(0xFFFF)"
       << uint32var.load() << endl;

  uint32var.fetch_or(0x00FF);
  cout << "std::atomic<uint32_t> uint32var - fetch_or(0x00FF)"
       << uint32var.load() << endl;

  uint32_t uintval{10};
  uint32var.store(10);
  uint32var.compare_exchange_strong(uintval, 1000);
  cout << "std::atomic<uint32_t> uint32var - compare_exchange_strong(10, 1000) "
          " - "
       << uint32var.load() << endl;

  // упорядочение доступа к памяти для атомарных операций

  // memory_order_relaxed - ослабленное упорядочение

  // memory_order_consume - захват освобождение
  // memory_order_acquire -
  // memory_order_release -
  // memory_order_acq_rel -

  // memory_order_seq_cst - последовательно согласованное упорядочение

  // flag.test_and_set(std::memory_order_seq_cst);

  int *ptr = nullptr;
  std::atomic_init(&atomic_ptr, ptr);

  ptr = (int *)malloc(16);

  std::thread t7([&]() {
    for (int i = 0; i < 16; i++) {
      ptr[i] = i;
    }
    atomic_ptr.store(ptr);
  });

  std::thread t8([&]() {
    while (!atomic_ptr.load()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    for (int i = 0; i < 16; i++) {
      std::cout <<"0x"<< std::hex << ptr[i] << std::endl;
    }
  });

  t7.join();
  t8.join();

  free(ptr);
}


#include "tools.h"

////функция для простого потока
// void thfunc() {
//  std::initializer_list<int> ini{2, 4, 5, 6, 7, 8, 9};

//  for (auto x : ini)
//    std::cout << "x = " << x << std::endl;
//}

// void thf(int a) {
//  for (int i = 0; i < a; i++)
//    std::cout << "Hello from second thread" << std::endl;
//}

////работа с потоками по новому стандарту С++17
// void test_number_1() {
//  //создание простого потока
//  std::cout << std::endl;
//  std::thread t1(thfunc);
//  t1.join();

//  //создание потока и передача параметров в функцию потока
//  std::cout << std::endl;
//  std::thread t2(thf, 2);
//  t2.join();

//  //создание потока и передача ему объекта-функтора
//  std::cout << std::endl;
//  std::thread t3((background_task())); //первый способ передачи
//  объекта-функтора
//                                       //в дополнительных скобках
//  t3.join();

//  std::cout << std::endl;
//  std::thread t4{background_task(
//      1)}; //второй способ передачи объекта-функтора в фигурных {} скобках
//  t4.join();

//  //создание потока и передача ему лямбда выражения
//  std::cout << std::endl;
//  auto lambda = [](int a) { std::cout << "a = " << a << std::endl; };

//  std::thread t5(lambda, 3);
//  t5.join();

//  //тестирование безопасного завершения потока
//  std::cout << std::endl;
//  std::thread t6{background_task()};
//  t6.join();
//  // thread_guard tg(t6);

//  //тестирование безопасного завершения потока при возникновении
//  исключительной
//  //ситуации
//  std::cout << std::endl;
//  auto l = [](int a) {
//    try {
//      if (a == 0)
//        throw std::runtime_error("a = 0 !!!");

//      std::cout << "1/a = " << static_cast<double>(1.0 /
//      static_cast<double>(a))
//                << std::endl;
//    } catch (std::exception &e) {
//      std::cout << "EXCEPTION " << e.what() << std::endl;
//    }
//  };

//  std::thread t7(l, 0);
//  // t7.join();
//  thread_guard tguard(t7);

//  //создание потока и передача ему функции-члена класса
//  std::cout << std::endl;
//  Xth x(3);
//  std::thread t8(&Xth::do_some_thing, &x, std::string("xxxx----xxxx"));
//  t8.join();
//}

////второй тест (передача параметров для функции потока)
////----------------------------------------------------
// void tst_param(int a, float &b, std::string &str, std::string &buf) {
//  std::cout << "data inserted into thread\n";
//  std::cout << "a = " << a << " b = " << b << " str = " << str
//            << " buf = " << buf << std::endl;

//  a = 4;

//  b = 2.71f;

//  str.clear();
//  str.append("900");

//  buf.clear();
//  buf.append("900");

//  std::cout << "\ndata changed from thread\n";
//  std::cout << "a = " << a << " b = " << b << " str = " << str
//            << " buf = " << buf << std::endl;
//}

// void test_number_2() {

//  //передача параметров функции потока: по значению, по ссылке
//  int a{9};
//  float b{3.14f};
//  char buffer[256];

//  memset(buffer, '\0', 256);

//  sprintf(buffer, "%i", 256);

//  std::string stbuff("345");

//  std::thread t1(tst_param, a, std::ref(b), std::ref(stbuff),
//                 std::string(buffer));
//  t1.join();

//  std::cout << '\n';
//  std::cout << "data from main thread\n";
//  std::cout << "a = " << a << " b = " << b << " str = " << stbuff
//            << " buf = " << buffer << std::endl;

//  //передача параметров функции члена класса
//  int A = 7;
//  int B = 8;
//  int C = 9;
//  std::cout << "\n Data before thread A = " << A << " B = " << B << " C = " <<
//  C
//            << std::endl;

//  Xth x(2);

//  std::thread t2(&Xth::clear, &x, std::ref(A), std::ref(B), std::ref(C));
//  t2.join();

//  std::cout << "\n Data after thread A = " << A << " B = " << B << " C = " <<
//  C
//            << std::endl;

//  A = 1;
//  B = 1;
//  C = 1;

//  X y(3);
//  std::thread t3(&X::increment_2, &y, std::ref(A), std::ref(B), std::ref(C));
//  t3.join();

//  std::cout << "\n Data after thread A = " << A << " B = " << B << " C = " <<
//  C
//            << std::endl;
//}

////тестирование семантики перемещения для объектов std::thread
////-----------------------------------------------------------
// void f() {
//  std::thread::id id = std::this_thread::get_id();
//  std::cout << "thread id " << id << std::endl;
//}

// void func(std::string &s) { std::cout << "\n s = " << s << std::endl; }

// void test_number_3() {
//  //поддержка семантики перемещения для объектов std::thread
//  std::thread t1(f);
//  std::thread t2;
//  std::thread t3 = std::move(t1);

//  std::string str("hello");

//  t1 = std::thread(func, std::ref(str));
//  t2 = std::move(t1);

//  if (t3.joinable())
//    t3.join();

//  if (t2.joinable())
//    t2.join();
//}

//---------------------------------------------------------------------------
//тестирование интеллектуальных указателей
//---------------------------------------------------------------------------

void PrintIntArray(int *p) {
  for (int i = 0; i < 10; i++) {
    std::cout << p[i] << " ";
  }
  std::cout << '\n';
}

//функция для простого удаления массива
void deleter(int *p) {
  std::cout << "\n function deleter() ";
  PrintIntArray(p);
  delete[] p;
}

//функтор для простого удаления массива
class Deleter {
 public:
  void operator()(int *p) {
    std::cout << "\n functor Deleter()  ";
    PrintIntArray(p);
    delete[] p;
  }
};

void TestSharedPtr() {
  //простой тест shared_ptr<int>  разными функциями удаления:
  // deleter - лямбда выражение
  std::shared_ptr<int> ptr_int_array(new int[10], [](int *p) {
    std::cout << "\n lambda deleter     ";
    PrintIntArray(p);
    delete[] p;
  });

  // deleter - функция
  std::shared_ptr<int> ptr_array(new int[10], deleter);
  // deleter - функтор
  std::shared_ptr<int> ptr_array2(new int[10], Deleter());

  for (int i = 0; i < 10; i++) {
    ptr_int_array.get()[i] = (10 - i);
    ptr_array.get()[i] = (100 - i);
    ptr_array2.get()[i] = (i - 15);
  }

  ptr_int_array = nullptr;
  ptr_array = nullptr;
  ptr_array2 = nullptr;

  std::cout << std::endl;
}

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
    std::cout << " All resoures was returned\n";
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

void TestIntelPtrsHard() {
  //более сложное использование shared_ptr указателей со своей стратегией
  //удаления
  std::shared_ptr<std::string> pstr(
      new std::string("Hello"), [](std::string *p) {
        std::cout << "\nYou deleted string: " << (*p) << std::endl;
        delete p;
      });

  std::cout << "\n pstr: " << (*pstr) << std::endl;
  pstr = nullptr;

  std::shared_ptr<int> ptr_array(new int[10], [](int *p) {
    std::cout << "\nYou deleted array: ";
    PrintIntArray(p);
    delete[] p;
  });

  for (int i = 0; i < 10; i++) {
    ptr_array.get()[i] = i;
  }

  std::cout << "Array was initialiazed \n";
  std::cout << "Array has values   ";

  for (int i = 0; i < 10; i++) {
    std::cout << ptr_array.get()[i] << " ";
  }

  ptr_array = nullptr;

  std::cout << std::endl
            << "ptr_array.use_count() = " << ptr_array.use_count() << std::endl;

  std::shared_ptr<SuperData> super_data_ptr(
      new SuperData(), [](SuperData *spd) {
        std::cout << "\n removing SuperData ptr\n";
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

////тестирование уникальных указателей unique_ptr<>
////-----------------------------------------------
// unique_ptr<string> createString(char const *charArray) {
//  return unique_ptr<string>(new string(charArray));
//}

// void printString(unique_ptr<string> ps) {
//  cout << "\n Your string is " + *ps << endl;
//}

// void fdeleter(int *p) {
//  cout << "\n You will delete array with function \'fdeleter\' " << endl;
//  delete[] p;
//}

// void test_unique_ptr() {
//  //тестирование базовых возможностей уникальных указателей
//  std::unique_ptr<int[], void (*)(int *)> up(new int[10], [](int *p) {
//    std::cout << "delete array " << std::endl;
//    for (int i = 0; i < 10; i++)
//      std::cout << "x = " << p[i] << std::endl;

//    delete[] p;
//  });

//  for (int i = 0; i < 10; i++)
//    up[i] = i;

//  up = nullptr;
//}

// void test_unique_ptrs() {
//  //базовые возможности
//  unique_ptr<string> pStr(new string("uma"));

//  (*pStr)[0] = 'U';
//  cout << "\nString = " << *pStr << endl;

//  pStr->append("-puma");
//  cout << "\nString = " << *pStr << endl;

//  (*pStr)[2] = 'A';
//  cout << "\nString = " << *pStr << endl;

//  pStr = nullptr;

//  //указатель на массив строк
//  unique_ptr<string[]> text(new string[5]);

//  text[0] = string("Hello");
//  text[1] = string("unique_ptr<>");
//  text[2] = string(" it is cool");
//  text[3] = string("very cool and fun");
//  text[4] = string("OK");

//  cout << '\n';

//  for (int i = 0; i < 5; i++)
//    cout << text[i] << " ";

//  text = nullptr;

//  //указатель на массив строк со своим удалителем
//  unique_ptr<string[], void (*)(string *)> page(new string[5], [](string *p) {
//    cout << "\nYou will delete a page of text\n";
//    delete[] p;
//  });

//  page[0] = string("Hello");
//  page[1] = string("unique_ptr<>");
//  page[2] = string(" it is cool");
//  page[3] = string("very cool and fun");
//  page[4] = string("OK");

//  cout << '\n';
//  for (int i = 0; i < 5; i++)
//    cout << page[i] << " ";

//  page = nullptr;

//  //потеря владения объектом
//  unique_ptr<string> upStr(new string("Object"));

//  string *str =
//      upStr.release(); //вызов функции release() - приводит к потере владения

//  cout << "\n str - " << *str << endl;

//  delete str;

//  //передача владения
//  unique_ptr<string> ps(new string("Super Object"));

//  upStr = std::move(ps); //передача владения std::move()

//  cout << '\n';
//  cout << "unique_ptr<string> upStr has - " << *upStr << endl;

//  upStr = nullptr;

//  if (ps)
//    cout << "\n ps is owner of object\n";
//  else
//    cout << "\n ps is not owner of object\n";

//  ps = nullptr;

//  //передача владения 2
//  unique_ptr<int, void (*)(int *)> up1(new int, [](int *p) {
//    cout << "\n delete up1\n";
//    delete p;
//  });
//  *up1 = 2;

//  unique_ptr<int, void (*)(int *)> up2(new int, [](int *p) {
//    cout << "\n delete up2\n";
//    delete p;
//  });
//  *up2 = 4;

//  up2 = std::move(up1); //для потерянного объекта связанного с up2 - будет
//                        //вызвана функция удаления

//  cout << "\n up2 -> " << *up2 << endl;

//  up1 = unique_ptr<int, void (*)(int *)>(new int, [](int *p) {
//    delete p;
//  }); //пустому unique_ptr<> присваиваем новое значение
//  *up1 = 10;
//  cout << "\n up1 -> " << *up1 << endl;

//  //исток и сток для unique_ptr<>
//  unique_ptr<string> p = createString("America");

//  printString(std::move(p));

//  //операторы удаления
//  unique_ptr<int, void (*)(int *)> up3(new int[4], [](int *p) {
//    cout << "\n declaration void(*)(int*)\n";
//    delete[] p;
//  });

//  unique_ptr<int, std::function<void(int *)>> up4(new int[10], [](int *p) {
//    cout << "\n declaration std::function<void(int*)> \n";
//    delete[] p;
//  });

//  auto l = [](int *p) {
//    cout << "\n declaration decltype(l)";
//    delete[] p;
//  };

//  unique_ptr<int, decltype(l)> up5(new int[8], l);

//  unique_ptr<int, std::function<void(int *)>> up7(new int[10], fdeleter);

//  unique_ptr<int, decltype(ArrayDeleter())> up8(new int[2], ArrayDeleter());
//}

////тестирование идентификации потоков
////----------------------------------------------
// void some_work() {
//  std::thread::id id = std::this_thread::get_id();
//  cout << "\nThread id - " << id << endl;
//}

// void test_threads_id() {
//  //тестирование получения id потока
//  std::thread::id thisId =
//      std::this_thread::get_id(); //получим id текущего потока

//  int numThreads =
//      std::thread::hardware_concurrency(); //получаем сколько потоков возможно
//                                           //по настоящему

//  cout << "\n System has hardware concurrency - " << numThreads << endl;
//  cout << "\n This thread id - " << thisId << endl;

//  std::vector<std::thread> poolThreads(
//      numThreads); //резервируем размер вектора для потоков
//  for (int i = 0; i < numThreads; i++) {
//    poolThreads.push_back(std::thread(some_work));
//  }

//  std::for_each(poolThreads.begin(), poolThreads.end(),
//                ThreadJointer()); //поочередный вызов join() для каждого
//                потока

//  // std::vector<std::thread>::iterator t;
//  // for (t = poolThreads.begin(); t != poolThreads.end(); ++t )
//  //{
//  //	if ((*t).joinable())
//  //	{
//  //		cout << "\n Thread with id " << (*t).get_id() << " joined" <<
//  // endl;
//  //		(*t).join();
//  //	}
//  //}

//  poolThreads.clear();
//}

////тестиование мьютексов
////-----------------------------------------------------------
// void print_rec(string &s, std::recursive_mutex &mut) {
//  {
//    std::lock_guard<std::recursive_mutex> lguard(mut);

//    for (char c : s)
//      cout.put(c);

//    cout << endl;
//  }
//}

// void print(string &s, std::mutex &mut) {
//  {
//    std::lock_guard<std::mutex> lguard(mut);

//    for (char c : s)
//      cout.put(c);

//    cout << endl;
//  }
//}

// void reverseString(string &str, std::recursive_mutex &rec_mutex) {
//  {
//    std::lock_guard<std::recursive_mutex> lg(rec_mutex);

//    string copy_str(str);
//    str.clear();

//    for (auto i = copy_str.rbegin(); i != copy_str.rend(); ++i) {
//      string ch{*i};
//      str.append(ch);
//    }
//    print_rec(str, rec_mutex);
//  }
//}

// int someWorkWhileMutexBusy() {
//  static int i = 0;
//  i++;
//  return i;
//}

// void swap(int &a, int &b) {
//  a = a + b;
//  b = a - b;
//  a = a - b;
//}

// void test_mutex() {
//  //использование простого мьютекса
//  std::mutex mut;

//  string strhello("Hello mutex");
//  string strgoodday("Good day");
//  string strgoodmorning("Good morning");

//  std::thread t1(print, std::ref(strhello), std::ref(mut));
//  std::thread t2(print, std::ref(strgoodday), std::ref(mut));

//  print(strgoodmorning, mut);

//  t1.join();
//  t2.join();

//  cout << endl;

//  //использование рекурсивных мьютексов (3 потока конкурируют за доступ к
//  строке
//  //и за доступ в консоль)
//  std::recursive_mutex rec_mutex;

//  std::thread t3(reverseString, std::ref(strhello), std::ref(rec_mutex));
//  std::thread t4(reverseString, std::ref(strhello), std::ref(rec_mutex));
//  std::thread t5(reverseString, std::ref(strhello), std::ref(rec_mutex));

//  t3.join();
//  t4.join();
//  t5.join();

//  cout << endl;

//  //тестирование попытки блокировки
//  std::mutex try_mutex;

//  std::thread t6([&]() {
//    {
//      std::lock_guard<std::mutex> lgd(try_mutex);
//      for (int i = 0; i < 500; i++)
//        cout << "t6";
//    }
//  });

//  int counter = 0;
//  while (try_mutex.try_lock() == false) {
//    counter = someWorkWhileMutexBusy();
//  }

//  {
//    std::lock_guard<std::mutex> lockgrd(try_mutex, std::adopt_lock);
//    cout << endl;
//    cout << "counter =  " << counter << endl;
//  }

//  t6.join();

//  //тестирование std::timed_mutex  и std::recursive_timed_mutex
//  std::timed_mutex t_mutex;

//  //поток будет работать 3 секунды и блокировать мьютекс
//  std::thread t7([&]() {
//    {
//      std::lock_guard<std::timed_mutex> tlg(t_mutex);
//      for (int i = 0; i < 3; i++) {
//        cout << "pause 1 sec - "
//             << "t7" << endl;
//        std::this_thread::sleep_for(std::chrono::seconds(1)); //пауза в 1 sec
//      }
//    }
//  });

//  //будем пытаться захватить мьютекс 4 сек
//  if (t_mutex.try_lock_for(std::chrono::seconds(4))) {
//    {
//      std::lock_guard<std::timed_mutex> tlguard(t_mutex, std::adopt_lock);
//      cout << endl;
//      cout << "timeout end" << endl;
//    }
//  } else {
//    std::this_thread::sleep_for(std::chrono::seconds(2));
//    cout << endl;
//    cout << "mutex is busy more then " << 4 << " sec" << endl;
//  }

//  t7.join();

//  //работа с несколькими блокировками
//  cout << endl;
//  cout << "Test multiple mutex blocking" << endl;

//  std::mutex mut1;
//  std::mutex mut2;
//  std::mutex mut3;

//  int val_1{10};
//  int val_2{5};

//  auto lambda_swap = [&]() {
//    {
//      int index_failure_lock =
//          0; //будет содержать индекс первой неудачной блокировки
//      index_failure_lock =
//          std::try_lock(mut1, mut2, mut3); //попытка блокировки трех мьютексов

//      // std::lock(mut1, mut2, mut3);
//      // //запрос на блокировку трех мьютексов
//      if (index_failure_lock < 0) {
//        std::lock_guard<std::mutex> lgdMut1(mut1, std::adopt_lock);
//        std::lock_guard<std::mutex> lgdMut2(mut2, std::adopt_lock);
//        std::lock_guard<std::mutex> lgdMut3(mut3, std::adopt_lock);

//        cout << endl << "thread id - " << std::this_thread::get_id() << endl;
//        cout << "before swaping  val_1 = " << val_1 << " val_2 = " << val_2
//             << endl;

//        swap(val_1, val_2);

//        cout << "After swaping   val_1 = " << val_1 << " val_2 = " << val_2
//             << endl;
//      } else {
//        std::lock_guard<std::mutex> lgdMut3(mut3);
//        cout << endl
//             << "thread id - " << std::this_thread::get_id()
//             << "  cannot block mutex with index - " << index_failure_lock
//             << endl;
//      }
//    }
//  };

//  std::thread t8(lambda_swap);
//  std::thread t9(lambda_swap);
//  std::thread t10(lambda_swap);

//  t8.join();
//  t9.join();
//  t10.join();
//}

//// unique_lock()
// void test_unique_lock() {
//  std::mutex mut;

//  string s("shared string");

//  std::thread t1([&]() {
//    std::unique_lock<std::mutex> l(
//        mut, std::defer_lock); //создали защиту для мьютекса но не
//        заблокировали

//    l.lock();
//    s.append("_t1_");
//    cout << endl << "our string is - " << s << endl;
//    l.unlock();
//  });

//  std::thread t2([&]() {
//    std::unique_lock<std::mutex> l(
//        mut, std::defer_lock); //создали защиту для мьютекса но не
//        заблокировали

//    l.lock(); //блокировка
//    s.append("_t2_");
//    cout << endl << "our string is - " << s << endl;
//    l.unlock(); //разблокировка
//  });

//  std::thread t3([&]() {
//    {
//      std::unique_lock<std::mutex> ul(
//          mut, std::try_to_lock); //попытка заблокировать мьютекс
//      if (ul) {
//        s.append("t3");
//        cout << endl << "our string is - " << s << endl;
//      } else
//        cout << endl << "t3 can not lock mutex " << endl;
//    }
//  });

//  {
//    std::unique_lock<std::mutex> lock(
//        mut); //создали защиту для мьютекса и сразу же заблокировали его
//    s.append("_main_thread_");
//    cout << endl << "our string is - " << s << endl;
//  }

//  t1.join();
//  t2.join();
//  t3.join();
//}

////тестиование condition  variables
////--------------------------------------------------
// void insertValue(int &val, std::queue<int> &qu, std::mutex &mut,
//                 std::condition_variable &cv) {
//  for (int i = 0; i < 10; i++) {
//    {
//      std::unique_lock<std::mutex> l(mut);
//      qu.push(val);
//      val++;
//    }
//    cv.notify_one();
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//  }
//}

// void getValue(std::queue<int> &qu, std::mutex &mut,
//              std::condition_variable &cv) {
//  for (int i = 0; i < 10; i++) {
//    {
//      std::unique_lock<std::mutex> ul(mut);
//      cv.wait(ul, [&]() -> bool { return !qu.empty(); });
//      cout << "val = " << qu.front() << endl;
//      qu.pop();
//    }
//  }
//}

// void test_condition_variables() {
//  //простое тестирование условных переменных
//  std::condition_variable condVar;
//  std::mutex mut;

//  bool ready = true;
//  string s("0");

//  std::thread t1([&]() {
//    for (int i = 0; i < 10; i++) {
//      {
//        std::unique_lock<std::mutex> ul(mut);
//        s.append("-");
//        cout << s << endl;
//        ready = true;
//      }
//      condVar.notify_one();
//      std::this_thread::sleep_for(std::chrono::seconds(2));
//    }
//  });

//  std::thread t2([&]() {
//    for (int i = 0; i < 10; i++) {
//      std::unique_lock<std::mutex> ul(mut);
//      condVar.wait(ul, [&]() -> bool { return ready; });
//      s.append("0");
//      cout << s << endl;
//      ready = false;
//      // std::this_thread::sleep_for(std::chrono::seconds(1));
//    }
//  });

//  t1.join();
//  t2.join();
//}

// void test_condition_variable_queue() {
//  //более сложный пример с очередью значений std::queue<int> qu
//  // std::queue<int> qu;
//  // std::condition_variable cond_var;
//  // std::mutex qmutex;

//  // int value{ 0 };

//  // std::thread t3(insertValue, std::ref(value), std::ref(qu),
//  // std::ref(qmutex), std::ref(cond_var)); std::thread t4(getValue,
//  // std::ref(qu), std::ref(qmutex), std::ref(cond_var));

//  // t3.join();
//  // t4.join();

//  //тестирование wait_for()
//  cout << endl << "Test condition_variable.wait_for()" << endl;
//  std::queue<int> qu;
//  std::condition_variable cvar;
//  std::mutex some_mutex;

//  std::thread t5([&]() {
//    std::unique_lock<std::mutex> lock(some_mutex, std::defer_lock);
//    lock.lock();
//    for (int i = 0; i < 4; i++) {
//      qu.push(i);
//    }
//    lock.unlock();
//    cvar.notify_one();
//    std::this_thread::sleep_for(std::chrono::milliseconds(10));
//  });

//  std::thread t6([&]() {
//    std::unique_lock<std::mutex> lock(some_mutex);
//    cvar.wait_for(lock, std::chrono::milliseconds(5),
//                  [&]() -> bool { return !(qu.empty()); });
//    for (int i = 0; i < 4; i++) {
//      cout << endl << "val = " << qu.front() << endl;
//      qu.pop();
//    }
//  });

//  t5.join();
//  t6.join();
//}

////тестирование объектов
////будущих результатов и асинхронного выполнения функций
// void async_func() { cout << endl << "Hello from async thread" << endl; }

// void fill_array(std::vector<int> &vec, int size, int i) {
//  std::default_random_engine dre(i);
//  std::uniform_int_distribution<int> id(1, 1000);

//  for (int j = 0; j < size; j++)
//    vec.push_back(id(dre));
//}

// string stringback(string s) {
//  char c;
//  int half_size = s.size() / 2;
//  int size = s.size();

//  for (int i = 0; i < half_size; i++) {
//    c = s[i];
//    s[i] = s[size - i - 1];
//    s[size - i - 1] = c;
//  }

//  return s;
//}

// void test_async_and_future() {
//  int N = 10;

//  std::future<int> intf = std::async(std::launch::async, [=]() -> int {
//    int sum = 0;
//    for (int i = 0; i < N; i++) {
//      sum += i;
//    }
//    return sum;
//  });

//  cout << "future<int> intf = " << intf.get() << endl;

//  std::future<string> strf =
//      std::async(std::launch::deferred, stringback,
//                 std::string("А роза упала на лапу азора"));

//  cout << endl << "std::future<string> strf = " << strf.get() << endl;

//  Xc x;
//  std::future<void> voidf = std::async(std::launch::deferred, &Xc::print_s,
//  &x,
//                                       string("function member"));

//  std::future<void> voidf2 =
//      std::async(std::launch::deferred, Xc(), string("123"));

//  cout << endl << "voidf = ";
//  voidf.get();

//  cout << endl << "voidf2 = ";
//  voidf2.get();
//  cout << endl;
//}

// void test_future_and_async() {
//  //простой тест асинхроного выполнеия функциональной сущности
//  int sum{0};
//  int a{5};
//  int b{2};

//  std::future<int> f1 = std::async([](int a) -> int { return a * a; }, a);

//  std::future<int> f2 = std::async([](int b) -> int { return b * b * b; }, b);

//  sum = f1.get() + f2.get();

//  cout << endl << "sum = " << sum << endl;

//  //отложеный вызов функциональной сущности
//  std::future<void> f3 = std::async(std::launch::deferred, async_func);
//  f3.get();

//  std::future<double> f4 = std::async(
//      std::launch::async, [](double d) -> double { return pow(d, 3); }, 3.0);
//  cout << endl << "3.0^3 = " << f4.get() << endl;

//  //ожидание будущих результатов, запрос состояния
//  std::vector<int> vec;

//  std::future<void> f5{
//      async(std::launch::async, fill_array, std::ref(vec), 10, 5)};
//  std::future_status status;
//  status = f5.wait_for(std::chrono::microseconds(10));

//  if (status == std::future_status::deferred)
//    cout << endl << "status - deferred" << endl;

//  if (status == std::future_status::ready)
//    cout << endl << "status - ready" << endl;

//  if (status == std::future_status::timeout)
//    cout << "status - timeout" << endl;

//  std::this_thread::sleep_for(std::chrono::seconds(2));

//  f5.get();

//  //разделяемые объекты будущих результатов
//  std::mutex mut;

//  std::shared_future<int> shf{std::async([&]() -> int {
//    int num{0};
//    cout << endl << "input num = ";
//    cin >> num;

//    if (!cin)
//      throw std::runtime_error("number is not valid");

//    return num;
//  })};

//  auto lam = [&]() {
//    {
//      try {
//        std::lock_guard<std::mutex> l(mut);
//        cout << endl
//             << "thread id " << std::this_thread::get_id()
//             << "  num = " << shf.get() << endl;
//      } catch (const std::exception &e) {
//        std::cerr << endl
//                  << "EXCEPTION in thread " << std::this_thread::get_id()
//                  << " : " << e.what() << endl;
//      }
//    }
//  };

//  auto f6{std::async(lam)};
//  auto f7{std::async(lam)};
//  auto f8{std::async(lam)};
//  auto f9{std::async(lam)};

//  //ждем завершения потоков
//  f6.get();
//  f7.get();
//  f8.get();
//  f9.get();
//}

////тестирование упакованных задач
////------------------------------------------------------
// double computeMul(double x, double y) { return x * y; }

// void test_packaged_task() {
//  //упакованная задача (сделанная из функции)
//  double x = 2.2, y = 2.0;

//  std::packaged_task<double(double, double)> pckt(computeMul);
//  std::future<double> fd{pckt.get_future()};

//  std::thread t1(std::move(pckt), x, y);
//  t1.join();

//  cout << endl
//       << "x = " << x << " y = " << y << " x * y = " << fd.get() << endl;

//  //упакованная задача (сделанная из лямбда выражения)
//  int a{8};
//  auto lambda{[&]() -> int { return (a * a); }};
//  std::packaged_task<int()> packaged_lambda(lambda);
//  std::future<int> fint{packaged_lambda.get_future()};

//  std::thread t2(std::move(packaged_lambda));

//  cout << endl << "a*a = " << fint.get() << endl;

//  t2.join();

//  //упакованная задача сделанная из функтора
//  std::packaged_task<void(string)> pacxc{Xc()};
//  std::future<void> fv{pacxc.get_future()};

//  std::thread t3(std::move(pacxc), std::string("Hello Xc"));
//  t3.join();

//  cout << endl << "Xc() - ";
//  fv.get();

//  //упакованная задача сделанная из функции члена класса
//}

////тестирование размеров указателей
////--------------------------------------------------------
// void test_pointers_size() {
//  //проверка размерности указателя
//  double s = 9.0;
//  double *ptr = &s;

//  int a = 9;
//  int *intPtr = &a;

//  char c{'h'};
//  char *pc{&c};

//  cout << endl
//       << "sizeof(double*) = " << sizeof(ptr)
//       << " sizeof(*double) = " << sizeof(s) << endl;
//  cout << endl
//       << "sizeof(int*)    = " << sizeof(intPtr)
//       << " sizeof(*int) = " << sizeof(a) << endl;
//  cout << endl
//       << "sizeof(char*)   = " << sizeof(pc) << " sizeof(*char) = " <<
//       sizeof(c)
//       << endl;
//}

//------------------------------------------------------------------------
//тестирование библиотечки хроно
//------------------------------------------------------------------------
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
  std::chrono::seconds seconds_(2);

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
  std::cout << std::endl << "max() " << dur_3_4_max.count() << std::endl;

  auto dur_3_4_min = std::chrono::duration<int, std::ratio<3, 4>>::min();
  std::cout << std::endl << "min() " << dur_3_4_min.count() << std::endl;

  std::cout << std::endl;
  std::cout << seconds_ << std::endl;
  std::cout << millisec_100 << std::endl;
  std::cout << microsec_10 << std::endl;
  std::cout << minutes << std::endl;
  std::cout << nanosec_100 << std::endl;
  std::cout << std::endl;

  // duration_cast<>
  std::chrono::seconds ffive(62);
  std::chrono::minutes m =
      std::chrono::duration_cast<std::chrono::minutes>(ffive);
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

////тестирование атомарных операций
////-------------------------------------------------------------------

// std::atomic<bool> bool_data(false);

// std::atomic<char> char_data(-4);
// std::atomic<unsigned char> uchar_data('F');

// std::atomic<short> short_data(-129);
// std::atomic<unsigned short> ushort_data(65000);

// std::atomic<int> int_data(0);
// std::atomic<unsigned int> uint_data(0);

// std::atomic<long> long_data(-1000);
// std::atomic<unsigned long> ulong_data(0);

// std::atomic<long long> llong_data(-1000);
// std::atomic<unsigned long long> ullong_data(0);

// std::atomic<uint32_t> uint32var;

//// std::atomic_flag flag(ATOMIC_FLAG_INIT);

// void test_atomic() {
//  //получение характеристик атомарных переменных
//  std::thread t1([]() {
//    get_atomic_info(bool_data);
//    get_atomic_info(char_data);
//    get_atomic_info(uchar_data);
//    get_atomic_info(short_data);
//    get_atomic_info(ushort_data);
//    get_atomic_info(int_data);
//    get_atomic_info(uint_data);
//    get_atomic_info(long_data);
//    get_atomic_info(ulong_data);
//    get_atomic_info(llong_data);
//    get_atomic_info(ullong_data);
//  });

//  if (t1.joinable())
//    t1.join();

//  //работа с атомарными переменными
//  uint_data.store(10); //атомарная инициализация

//  std::thread t3([]() {
//    while (auto a = uint_data.load()) {
//      cout << "atomic unsigned int data: " << a << endl;
//      std::this_thread::sleep_for(std::chrono::milliseconds(50));
//    }
//  });

//  std::thread t4([]() {
//    for (;;) {
//      uint_data.fetch_sub(1);
//      std::this_thread::sleep_for(std::chrono::milliseconds(100));

//      if (!uint_data.load())
//        break;
//    }
//  });

//  if (t3.joinable())
//    t3.join();

//  if (t4.joinable())
//    t4.join();

//  //синхронизация доступа к данным на основе std::atomic<bool> bool_data;
//  data_Ty dty{2, 3, 5.2, "Hello string"};

//  std::thread t5([&]() {
//    std::this_thread::sleep_for(std::chrono::milliseconds(50));

//    dty.a = 7;
//    dty.b = 7;
//    dty.f = 7.0;
//    dty.s = "Thread t5";

//    bool_data.store(true);
//  });

//  std::thread t6([&]() {
//    while (!bool_data.load()) {
//      cout << "data not ready" << endl;
//      std::this_thread::sleep_for(std::chrono::milliseconds(5));
//    }

//    cout << dty << endl;
//  });

//  t5.join();
//  t6.join();

//  //демонстрация атомарных операций с атомарными переменными
//  std::atomic_init(&uint32var, 100);
//  cout << "std::atomic<uint32_t> uint32var - " << uint32var.load() << endl;

//  uint32var.fetch_add(10);
//  cout << "std::atomic<uint32_t> uint32var - fetch_add(10)    "
//       << uint32var.load() << endl;

//  uint32var.fetch_sub(90);
//  cout << "std::atomic<uint32_t> uint32var - fetch_sub(90)    "
//       << uint32var.load() << endl;

//  uint32var.store(50);
//  cout << "std::atomic<uint32_t> uint32var - store(50)        "
//       << uint32var.load() << endl;

//  cout << "std::atomic<uint32_t> uint32var - exchange(0x5555) "
//       << uint32var.exchange(0x5555) << endl;
//  cout << "new value -  " << uint32var.load() << endl;

//  uint32var.fetch_and(0xFFFF);
//  cout << "std::atomic<uint32_t> uint32var - fetch_and(0xFFFF)"
//       << uint32var.load() << endl;

//  uint32var.fetch_or(0x00FF);
//  cout << "std::atomic<uint32_t> uint32var - fetch_or(0x00FF)"
//       << uint32var.load() << endl;

//  uint32_t uintval{10};
//  uint32var.store(10);
//  uint32var.compare_exchange_strong(uintval, 1000);
//  cout << "std::atomic<uint32_t> uint32var - compare_exchange_strong(10, 1000)
//  "
//          "- "
//       << uint32var.load() << endl;

//  //упорядочение доступа к памяти для атомарных операций

//  // memory_order_relaxed - ослабленное упорядочение

//  // memory_order_consume - захват освобождение
//  // memory_order_acquire -
//  // memory_order_release -
//  // memory_order_acq_rel -

//  // memory_order_seq_cst - последовательно согласованное упорядочение

//  // flag.test_and_set(std::memory_order_seq_cst);
//}

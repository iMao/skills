
//#include "src/algo/algo.h"
//#include "src/oop/oop.h"
#include "../src/std11/study_stl.h"
#include "../src/std11/tools.h"

#include <iostream>

int main() {
  std::cout << "Hello C++11" << std::endl;
  //--------------------------------------------------------------
  //тесты многопоточности
  //--------------------------------------------------------------
  // test_number_1();
  // test_number_2();
  // test_number_3();
  // test_threads_id();

  //--------------------------------------------------------------
  // тесты интелектуальных указателей
  //--------------------------------------------------------------
  // TestSharedPtr();
  // TestIntelPtrs();
  // TestIntelPtrsHard();
  // TestUniquePtrs();

  //---------------------------------------------------------------
  // тесты мьютексов
  //---------------------------------------------------------------
  // test_mutex();
  // test_unique_lock();

  //---------------------------------------------------------------
  // тесты условных переменных
  //---------------------------------------------------------------
   test_condition_variables();
  // test_condition_variable_queue();


  // TestAsyncAndFuture();
  // TestFutureAndAsync();
  // test_packaged_task();
  // TestChronoLibrary();
  // test_atomic();

  // --------------------------------------------------------------
  // тесты потоков ввода вывода
  // --------------------------------------------------------------
  // test_fstreams();
  // test_string_streams();

  //тесты ООП
  // --------------------------------------------------------------
  // test_class();
  // test_multiple_inheritance();
  // test_access_declaration();
  // test_virtual_functions();
  // test_abstract_class();
  // test_oop_features();

  //тесты алгоритмов
  //--------------------------------------------------------
  // test_liner_list();

  return 0;
}

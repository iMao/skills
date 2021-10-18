
//#include "src/algo/algo.h"
//#include "src/oop/oop.h"
#include "../src/std11/study_stl.h"
#include "../src/std11/tools.h"

//#include <iostream>

int main() {
  std::cout << "Hello C++11" << std::endl;
  //тесты многопоточности, синхронизации и пр.
  //--------------------------------------------------------------
  // test_number_3();
  // TestSharedPtr();
  // TestIntelPtrs();
  // TestIntelPtrsHard();
  // TestUniquePtr();
  // TestUniquePtrs();
  // test_threads_id();
  // test_mutex();
  // test_unique_lock();
  // test_condition_variables();
  // test_condition_variable_queue();
  TestAsyncAndFuture();
  TestFutureAndAsync();
  // test_packaged_task();
  // TestChronoLibrary();
  // test_atomic();

  //тесты STL
  // --------------------------------------------------------------
  // TestArray();
  // test_pairs();
  // test_tuples();
  // test_vector();
  // test_deque();
  // test_list();
  // test_list_special();
  // test_forward_list();
  // test_sets();
  // test_multisets();
  // test_maps();
  // test_unordered_sets();

  //тесты потоков ввода вывода
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

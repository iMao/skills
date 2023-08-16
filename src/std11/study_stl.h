#ifndef SRC_CPP11_STL_STUDY_STL_
#define SRC_CPP11_STL_STUDY_STL_

#include <fstream>
#include <iomanip>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>

#include <array>
#include <deque>
#include <forward_list>
#include <initializer_list>
#include <list>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

#include <algorithm>
#include <numeric>
#include <typeinfo>
#include <utility>

#include <cctype>
#include <exception>
#include <functional>
#include <locale>
#include <random>

#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------------
//тестирование массива std::array<>
//------------------------------------------------------------------------------
template <typename t, std::size_t n>
void PrintArray(const char *array_name, const std::array<t, n> &a) {
  std::cout << array_name << ":  ";
  if (a.empty()) {
    std::cout << " is empty\n";
  }

  for (auto &x : a) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
}

template <typename t, std::size_t n>
void CompareArrays(const char *name_a, const std::array<t, n> &a,
                   const char *name_b, const std::array<t, n> &b) {
  std::cout << "arrays compared: ";
  if (a == b) {
    std::cout << name_a << " == " << name_b;
  } else {
    if (a > b) {
      std::cout << name_a << " > " << name_b;
    } else {
      std::cout << name_a << " < " << name_b;
    }
  }
  std::cout << std::endl;
}

template <typename t, int16_t n> class OArray {
private:
  t array_[n];

public:
  OArray() {
    for (int16_t i = 0; i < n; i++) {
      array_[i] = i;
    }
  }

  OArray(t val) {
    for (int16_t i = 0; i < n; i++) {
      array_[i] = val;
    }
  }

  ~OArray() {}

  bool operator==(const OArray &object) {
    for (int16_t i = 0; i < n; i++) {
      if (this->array_[i] != object.array_[i])
        return false;
    }
    return true;
  }

  bool operator!=(const OArray &object) { return !((*this) == (object)); }

  void Print() {
    std::cout << "Object array: ";
    for (int16_t i = 0; i < n; i++) {
      std::cout << array_[i] << " ";
    }
    std::cout << std::endl;
  }
};

namespace tools {

template <size_t n> void RandomFillArray(std::array<uint8_t, n> &arr) {
  for (size_t i = 0; i < n; i++) {
    arr[i] = i;
  }

  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(arr.begin(), arr.end(), g);
}

/**
 *HistSortArray - гистограммная сортировка массива
 */
template <size_t n> void HistSortArray(std::array<uint8_t, n> &arr) {
  std::array<int, 256> hist{};

  for (int i = 0; i < n; i++) {
    uint8_t val = arr[i];
    hist[val]++;
  }

  size_t k = 0;
  for (uint16_t i = 0; i < 256; i++) {
    for (int j = 0; j < hist[i]; j++) {
      arr[k] = i;
      k++;
    }
  }
}

} // namespace tools

void TestArray();

//------------------------------------------------------------------------------
//тестирование std::pair<T1,T2>p
//------------------------------------------------------------------------------
template <typename t1, typename t2>
std::ostream &operator<<(std::ostream &ostr, const std::pair<t1, t2> &p) {
  return ostr << "[" << p.first << "," << p.second << "]";
}

template <typename t>
std::pair<bool, std::pair<t, t>> SolveEquation(t a, t b, t c) {
  t D = b * b - 4 * a * c;
  if (D < 0) {
    return std::make_pair(false,
                          std::make_pair(static_cast<t>(0), static_cast<t>(0)));
  }

  t x1 = (-b - sqrt(D)) / (2 * a);
  t x2 = (-b + sqrt(D)) / (2 * a);

  return std::make_pair(true, std::make_pair(x1, x2));
}

void TestPairs();

//------------------------------------------------------------------------------
//тестирование кортежей std::tuple<T1,T2,...Tn> t
//------------------------------------------------------------------------------
void TestTuples();

//------------------------------------------------------------------------------
//тестирование контейнера std::vector<>
//------------------------------------------------------------------------------
template <typename t>
void PrintVectorInfo(const std::vector<t> &vec, const char *vec_name) {
  std::cout << std::endl;
  //текущее количество элементов
  std::cout << vec_name << ".size() = " << vec.size() << std::endl;

  //максимальное количество элементов
  std::cout << vec_name << ".max_size() = " << vec.max_size() << std::endl;

  //количество элементов которое возможно разместить
  //без дополнительного выделения памяти
  std::cout << vec_name << ".capacity() = " << vec.capacity() << std::endl;
}

template <typename t>
void VectorEmptyInfo(const std::vector<t> &v, const char *vector_name) {
  std::cout << std::endl;
  if (v.empty())
    std::cout << vector_name << " - empty" << std::endl;
  else
    std::cout << vector_name << " - full" << std::endl;
}

template <typename t>
void PrintVector(const std::vector<t> &v, const char *vector_name) {
  std::cout << vector_name << ":  ";
  if (v.empty())
    std::cout << "vector is empty" << std::endl;
  else {
    for (auto e : v) {
      std::cout << e << " ";
    }
    std::cout << std::endl;
  }
}

template <typename t> void TestIterators(std::vector<t> &vec) {
  std::cout << "const iterator" << std::endl;
  typename std::vector<t>::const_iterator j;
  for (j = vec.cbegin(); j != vec.cend(); ++j) {
    std::cout << (*j) << " ";
  }

  std::cout << "\niterator" << std::endl;
  typename std::vector<t>::iterator i;
  for (i = vec.begin(); i != vec.end(); ++i) {
    (*i) *= 5;
    std::cout << (*i) << " ";
  }

  std::cout << "\nreverse iterator" << std::endl;
  typename std::vector<t>::reverse_iterator k;
  for (k = vec.rbegin(); k != vec.rend(); ++k) {
    (*k) *= -1;
    std::cout << (*k) << " ";
  }

  std::cout << "\nconst reverse iterator" << std::endl;
  typename std::vector<t>::const_reverse_iterator l;
  for (l = vec.crbegin(); l != vec.crend(); ++l) {
    std::cout << (*l) << " ";
  }
  std::cout << std::endl;
}

class Some {
private:
  int a_;
  std::string s_;

public:
  Some() {}
  Some(int a, std::string s) : a_(a), s_(s) {}
  ~Some() {}

  int GetA() { return a_; }
  std::string &GetS() { return s_; }
};

std::ostream &operator<<(std::ostream &ostr, Some &s);

void TestVector();

//------------------------------------------------------------------------------
//тестирование контейнера std::deque<>
//------------------------------------------------------------------------------
template <typename t> void PrintDequeInfo(const std::deque<t> &dq) {
  std::cout << std::endl;
  std::cout << "    size: " << dq.size() << std::endl;
  std::cout << "max_size: " << dq.max_size() << std::endl;
}

template <typename t> void PrintDeque(const std::deque<t> &dq) {
  std::cout << std::endl;
  if (dq.empty())
    std::cout << "deque is empty" << std::endl;
  else {
    std::cout << "deque: ";
    for (auto s : dq)
      std::cout << s << " ";
    std::cout << std::endl;
  }
}

void TestDeque();

//------------------------------------------------------------------------------
// тестирование контейнера  std::list<>
//------------------------------------------------------------------------------
template <typename t> void PrintList(const std::list<t> &lst) {
  std::cout << std::endl;
  if (lst.empty()) {
    std::cout << "List is empty" << std::endl;
  } else {
    std::cout << "list: ";
    for (auto x : lst)
      std::cout << x << " ";
    std::cout << std::endl;
  }
}

template <typename t> void PrintListInfo(const std::list<t> &lst) {
  std::cout << std::endl;
  std::cout << "    list.size(): " << lst.size() << std::endl;
  std::cout << "list.max_size(): " << lst.max_size() << std::endl;
}

class Rm {
public:
  Rm() = default;
  ~Rm() = default;
  bool operator()(int a) { return ((a % 2) == 0); }
};

class Near {
public:
  Near() = default;
  ~Near() = default;
  bool operator()(double &a, double &b) { return (std::fabs(a - b) < 0.5); }
};

void TestList();

void TestListSpecial();

//------------------------------------------------------------------------------
//тестирование контейнера  std::forward_list<>
//------------------------------------------------------------------------------
template <typename t> void PrintForwardList(const std::forward_list<t> &frwd) {
  std::cout << std::endl;
  if (frwd.empty()) {
    std::cout << std::endl << "forward_list is empty" << std::endl;
  } else {
    std::cout << "forward_list: ";
    for (t x : frwd)
      std::cout << x << " ";
    std::cout << std::endl;
  }
}

template <typename t>
void PrintForwardListInfo(const std::forward_list<t> &frwd) {
  std::cout << std::endl;
  std::cout << "frwd.empty()    " << std::boolalpha << frwd.empty()
            << std::endl;
  std::cout << "frwd.max_size() " << frwd.max_size() << std::endl;
  std::cout << "frwd.size()     " << std::distance(frwd.begin(), frwd.end())
            << std::endl;
}

template <typename InputIterator, typename t>
inline InputIterator findBefore(InputIterator first, InputIterator last,
                                const t &val) {
  if (first == last)
    return first;

  InputIterator next(first);
  ++next;
  while ((next != last) && !(*next == val)) {
    ++next;
    ++first;
  }
  return first;
}

template <typename InputIterator, typename Pred>
inline InputIterator findBefore_if(InputIterator first, InputIterator last,
                                   Pred pred) {
  if (first == last)
    return first;

  InputIterator next(first);
  ++next;
  while ((next != last) && !pred(*next)) {
    ++next;
    ++first;
  }
  return first;
}

template <typename InputIterator, typename t>
inline InputIterator findIterator(InputIterator first, InputIterator last,
                                  const t &value) {
  if (first == last)
    return first;

  while ((first != last) && (*first != value))
    ++first;

  return first;
}

//сравнение строк вне зависимости от регистра
class CompUpper {
public:
  bool operator()(std::string s1, std::string s2) {
    std::transform(s1.begin(), s1.end(), s1.begin(), toupper);
    std::transform(s2.begin(), s2.end(), s2.begin(), toupper);

    return (0 == s1.compare(s2));
  }
};

void TestForwardList();

//------------------------------------------------------------------------------
//тестирование множеств  std::set<>
//------------------------------------------------------------------------------
template <typename t, typename cmp> void print_set(std::set<t, cmp> &st) {
  std::cout << std::endl;
  if (!st.empty()) {
    for (t x : st)
      std::cout << "x = " << x << std::endl;
  } else {
    std::cout << "set is empty" << std::endl;
  }
}

template <typename InputIterator, typename t, typename cmp>
void print_set_beg_end(InputIterator beg, InputIterator end,
                       std::set<t, cmp> &st) {
  if (end != st.end())
    ++end;

  for (auto i = beg; i != end; ++i)
    std::cout << "x = " << (*i) << std::endl;
}

template <typename t, typename cmp> void bounds(std::set<t, cmp> &st, t val) {
  std::cout << std::endl;
  std::cout << "value = " << val << std::endl;
  std::cout << "lower_bound() " << *st.lower_bound(val) << std::endl;
  std::cout << "upper_bound() " << *st.upper_bound(val) << std::endl;
  std::cout << "equal_range()  (" << *st.equal_range(val).first << ") - ("
            << *st.equal_range(val).second << ")" << std::endl;
}

template <typename t, typename cmp> void print_set_info(std::set<t, cmp> &st) {
  std::cout << std::endl;
  std::cout << "set.size()      = " << st.size() << std::endl;
  std::cout << "set.max_size()  = " << st.max_size() << std::endl;
  std::cout << "set.empty()     = " << std::boolalpha << st.empty()
            << std::endl;
}

template <typename t, typename cmp>
void print_cmp_criteria(std::set<t, cmp> &st) {
  std::cout << "set.key_comp()   = " << st.key_comp() << std::endl;
  std::cout << "set.value_comp() = " << st.value_comp() << std::endl;
}

template <typename _Ty>
std::ostream &operator<<(std::ostream &ostr, std::less<_Ty> &ls) {
  return ostr << "Compare criteria less<t> means that [ (x0 < x1) == true ]";
}

template <typename _Ty>
std::ostream &operator<<(std::ostream &ostr, std::greater<_Ty> &gr) {
  return ostr
         << "Compare criteria greater<t> means that [ (x0 > x1) == true  ]";
}

class Num {
private:
  int a;

public:
  Num(int a) : a(a) {}
  ~Num() {}

  int get_a() { return a; }

  bool operator<(Num b) { return this->a < b.get_a(); }
};

template <typename t> struct NumLess {
  bool operator()(t a, t b) const { return a < b; }
};

std::ostream &operator<<(std::ostream &os, Num &num);

void test_sets();

//------------------------------------------------------------------------------
// тестирование мультимножеств  std::multiset<>
//------------------------------------------------------------------------------

template <typename t, typename cmp>
void print_multiset(std::multiset<t, cmp> &mset) {
  std::cout << std::endl;
  if (!mset.empty()) {
    for (t x : mset)
      std::cout << "x = " << x << std::endl;
  } else
    std::cout << "Multiset is empty" << std::endl;
}

void test_multisets();

//------------------------------------------------------------------------------
// тестирование отображений  std::map<>
//------------------------------------------------------------------------------
template <typename Key, typename Val, typename Cmp>
void print_map(std::map<Key, Val, Cmp> &mp) {
  std::cout << std::endl;
  if (!mp.empty()) {
    for (auto x : mp)
      std::cout << x << std::endl;
  } else
    std::cout << "Map is empty" << std::endl;
}

template <typename Key, typename Val, typename Cmp>
void mapbounds(std::map<Key, Val, Cmp> &mp, Key val) {
  std::cout << "Map bounds for "
            << "Val = " << val << std::endl;

  std::pair<Key, Val> lower_element, upper_element;

  lower_element = *mp.lower_bound(val);
  std::cout << "map.lower_bound() key1 = " << lower_element.first << std::endl;

  upper_element = *mp.upper_bound(val);
  std::cout << "map.upper_bound() key2 = " << upper_element.first << std::endl;

  std::pair<typename std::map<Key, Val, Cmp>::iterator,
            typename std::map<Key, Val, Cmp>::iterator>
      para_its = mp.equal_range(
          val); //функция возвращает пару итераторов std::pair<it1,it2>
  lower_element = *para_its.first;
  upper_element = *para_its.second;

  std::cout << "map.equal_range() = "
            << "[ key1 = " << lower_element.first
            << ", key2 = " << upper_element.first << "]" << std::endl;
}

//функция для замены ключа у элемента
template <typename Container>
inline bool replace_key(Container &c, typename Container::key_type &old_key,
                        typename Container::key_type &new_key) {
  typename Container::iterator pos;

  pos = c.find(old_key); //ищем элемент со старым ключом
  if (pos != c.end()) {
    c.insert(std::make_pair(
        new_key,
        pos->second)); //вставляем пару из нового ключа и старого значения
    c.erase(pos);      //удаляем старый элемент
    return true;
  } else
    return false;
}

class RealTimeCmp {
public:
  enum cmp_mode { normal, nocase };
  RealTimeCmp(cmp_mode m = normal) : mode(m) {}

  static bool nocase_compare(char c1, char c2) {
    return toupper(c1) < toupper(c2);
  }

  bool operator()(const std::string &s1, const std::string &s2) const {
    if (mode == normal)
      return s1 < s2;
    else
      return std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(),
                                          s2.end(), nocase_compare);
  }

private:
  cmp_mode mode;
};

void test_maps();

//тестирование неупорядоченных множеств и мультимножеств
// std::unorderd_set<> and std::unordered_multiset<>

template <typename t, typename hf, typename cmp>
void print_unordered_set(std::unordered_set<t, hf, cmp> &uset) {
  std::cout << std::endl;
  if (!uset.empty()) {
    for (t x : uset)
      std::cout << "x = " << x << std::endl;
  } else
    std::cout << "Unordered_set<t,hf,cmp> is empty" << std::endl;
}

template <typename t, typename hf, typename cmp>
void print_unordered_set_info(std::unordered_set<t, hf, cmp> &uset) {
  std::cout << std::endl;
  std::cout << "Количество сегментов                       - "
            << uset.bucket_count() << std::endl;
  std::cout << "Максимальное количество сегментов          - "
            << uset.max_bucket_count() << std::endl;
  std::cout << "Количество элементов                       - " << uset.size()
            << std::endl;
  std::cout << "Максимально возможное количество элементов - "
            << uset.max_size() << std::endl;
  std::cout << "Текущий коэффициент заполнения             - "
            << uset.load_factor() << std::endl;
  std::cout << "Максимальный коэффициент заполнения        - "
            << uset.max_load_factor() << std::endl;
}

template <typename t> std::size_t hashf(t val) {
  return (std::hash<t>()(val) + 0x9E3779B9);
}

class Customer {
private:
  std::string name;
  unsigned int check_sum;

public:
  Customer(std::string name = "Tom", unsigned int check_sum = 55)
      : name(name), check_sum(check_sum) {}
  std::string get_name() const { return name; }
  unsigned int get_check_sum() const { return check_sum; }

  bool operator==(const Customer &c1) const {
    return (this->check_sum == c1.get_check_sum()) &&
           (this->name.compare(c1.get_name()) == 0);
  }
};

std::ostream &operator<<(std::ostream &ostr, const Customer &c);

class CustomerHash {
public:
  std::size_t operator()(const Customer &c) const {
    return std::hash<unsigned int>()(c.get_check_sum()) +
           std::hash<std::string>()(c.get_name());
  }
};

class CustomerEqual {
public:
  bool operator()(const Customer &c1, const Customer &c2) const {
    return (c1.get_name().compare(c2.get_name()) == 0);
  }
};

void test_unordered_sets();

//------------------------------------------------------------------------------
//тестирование потоков ввода вывода
//------------------------------------------------------------------------------

void cin_properties(std::istream &cinth);

template <typename charT, typename traits>
inline std::basic_ostream<charT, traits> &
myendl(std::basic_ostream<charT, traits> &ostr) {
  ostr.put('\n');
  ostr.flush();

  return ostr;
}

template <typename charT, typename traits>
std::basic_ostream<charT, traits> &
myfformat(std::basic_ostream<charT, traits> &ostr) {
  ostr << std::setw(10) << std::setprecision(7) << std::fixed << std::showpos
       << std::right;

  return ostr;
}

template <typename charT, typename traits>
std::basic_ostream<charT, traits> &
RUB(std::basic_ostream<charT, traits> &ostr) {
  ostr.put(0xE282BD);
  ostr << std::setw(10) << std::setprecision(7) << std::fixed << std::showpos
       << std::right;

  return ostr;
}

enum LANG { C, RUS, RUS_UTF8, ENG, ENG_UTF8, DE, DE_UTF8, FR };

void set_locale(LANG lang);

//пользовательский модификатор для игнорирования n-строк
class ignoreLine {
private:
  int num;

public:
  explicit ignoreLine(int n = 1) : num(n) {}

  template <typename _char, typename _traits>
  friend std::basic_istream<_char, _traits> &
  operator>>(std::basic_istream<_char, _traits> &istr, const ignoreLine &ign) {
    for (int i = 0; i < ign.num; i++) {
      istr.ignore(std::numeric_limits<std::streamsize>::max(),
                  istr.widen('\n'));
    }
    return istr;
  }
};

void test_ithreads();

//------------------------------------------------------------------------------
//тестирование файловых потоков
//------------------------------------------------------------------------------
void test_fstreams();

//------------------------------------------------------------------------------
//тестирование строковыых потоков
//------------------------------------------------------------------------------

void test_string_streams();

#endif

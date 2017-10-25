#ifndef _STUDY_STL_
#define _STUDY_STL_

#include <stdlib.h>
#include <iostream>
#include <iomanip>


#include <math.h>
#include <string.h>

#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include <initializer_list>
#include <exception>
#include <utility>

#include <array>
#include <tuple>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <cctype>
#include <unordered_set>


#include <iosfwd>
#include <istream>
#include <ostream>




using std::cout;
using std::wcout;

using std::cin;
using std::wcin;

using std::endl;


using std::string;
using std::wstring;

//----------------------------------------------тестирование массива array<>------------------------------------------------------
template<typename t, int n>
void print_array(std::array<t, n>& a)
{
	cout << endl;
	for (auto x : a)
		cout << "x = " << x << endl;
}

template<typename t, int n>
void compare_arrays(std::array<t, n>& a, std::array<t, n>& b)
{
	if (a == b)
		cout << endl << " a == b" << endl;
	else
	{
		cout << endl << " a != b";

		if (a > b)
			cout << " and  a > b" << endl;
		else
			cout << " and  a < b" << endl;
	}
}

template<typename t, size_t n>
class Object
{
private:
	t a[n];

public:
	Object()
	{
		for (size_t i = 0; i < n; i++)
			a[i] = i;
	}

	Object(t val)
	{
		for (size_t i = 0; i < n; i++)
			a[i] = val;
	}

	~Object() {}


	bool operator==(Object& object)
	{
		for (size_t i = 0; i < n; i++)
		{
			if (this->a[i] != object.a[i])
				return false;
		}
		return true;
	}

	bool operator!=(Object& object)
	{
		return !((*this) == (object));
	}

	void print()
	{
		cout << endl;
		for (size_t i = 0; i < n; i++)
			cout << endl << " x = " << a[i];
	}

};

void test_array();

//---------------------------------------------тестирование std::pair<T1,T2>p------------------------------------------------------
template<typename t1, typename t2>
std::ostream& operator<<(std::ostream & ostr, std::pair<t1, t2> & p)
{
	return ostr << "[" << p.first << "," << p.second << "]";
}

template<typename t>
std::pair<t, t>& solve_equation(t a, t b, t c)
{
	t D = b*b - 4 * a*c;
	if (D < 0)
		return std::move(std::make_pair(static_cast<t>(0), static_cast<t>(0)));
	else
	{
		t x1 = (-b - sqrt(D)) / 2 * a;
		t x2 = (-b + sqrt(D)) / 2 * a;

		return std::move(std::make_pair( x1, x2 ));
	}
}

void test_pairs();

//---------------------------------------------тестирование кортежей std::tuple<T1,T2,...Tn> t-----------------------------
void test_tuples();

//---------------------------------------------тестирование контейнера std::vector<>---------------------------------------
template<typename t>
void print_vector_info(std::vector<t>& vec)
{
	cout << endl;
	cout << "vec.size()     = " << vec.size() << endl;		//текущее количество элементов
	cout << "vec.max_size() = " << vec.max_size() << endl;	//максимальное количество элементов
	cout << "vec.capacity() = " << vec.capacity() << endl;	//количество элементов которое возможно разместить без дополнительного выделения памяти
}

template<typename t>
void vector_empty_info(std::vector<t>& v)
{
	cout << endl;
	if (v.empty())
		cout << "v - empty" << endl;
	else
		cout << "v - full" << endl;
}

template <typename t>
void print_vector(std::vector<t>& v)
{
	cout << endl;
	if (v.empty())
		cout << "vector is empty" << endl;
	else
	{
		for (auto & e : v)
			cout << "e = " << e << endl;
	}
}

template <typename t>
void test_iterators(std::vector<t>& vec)
{
	cout << endl;
	std::vector<t>::const_iterator j;
	for (j = vec.cbegin(); j != vec.cend(); ++j)
		cout << "e = " << (*j) << endl;

	cout << endl;
	std::vector<t>::iterator i;
	for (i = vec.begin(); i != vec.end(); ++i)
	{
		(*i) *= 5;
		cout << "e = " << (*i) << endl;
	}

	cout << endl;
	std::vector<t>::reverse_iterator k;
	for (k = vec.rbegin(); k != vec.rend(); ++k)
	{
		(*k) *= -1;
		cout << "e = " << (*k) << endl;
	}

	cout << endl;
	std::vector<t>::const_reverse_iterator l;
	for(l = vec.crbegin(); l != vec.crend(); ++l)
		cout << "e = " << (*l) << endl;
}

class Some
{
private:
	int a;
	string s;

public:
	Some() {}
	Some(int a, string s) : a(a), s(s) {}
	~Some() {}

	int getA() { return a; }
	string& getS() { return s; }
};

std::ostream & operator<<(std::ostream & ostr, Some& s);

void test_vector();

//-------------------------------------тестирование контейнера std::deque<>------------------------------------------------
template<typename t>
void print_deque_info(std::deque<t>& dq)
{
	cout << endl;
	cout << "size - " << dq.size() << endl;
	cout << "max_size - " << dq.max_size() << endl;
}

template<typename t>
void print_deque(std::deque<t>& dq)
{
	cout << endl;
	if (dq.empty())
		cout << "deque is empty" << endl;
	else
	{
		for (auto & s : dq)
			cout << "dq - " << s << endl;
	}
}

void test_deque();

//-------------------------------------тестирование контейнера std::list<>-------------------------------------------------
template<typename t>
void print_list(std::list<t> & lst)
{
	cout << endl;
	if (!lst.empty())
	{
		for (t x : lst)
			cout << "x = " << x <<endl;
	}
	else
		cout << "List is empty" << endl;
}

template<typename t>
void print_list_info(std::list<t> & lst)
{
	cout << endl;
	cout << "list.size()     = " << lst.size() << endl;
	cout << "list.max_size() = " << lst.max_size() << endl;
}

class Rm
{
public:
	Rm() {};

	bool operator()(int a)
	{
		return ((a % 2) == 0);
	}
};

bool rmbig(int a);

void test_list();


bool same_integral_part(double & first, double & second);


class Near
{
public:
	bool operator()(double & a, double & b)
	{
		return (fabs(a - b) < 0.5);
	}
};


bool compare_pairs(std::pair<int, int>& p1, std::pair<int, int>& p2);

void test_list_special();

//------------------------------------------тестирование контейнера std::forward_list<>----------------------------------------------

template<typename t>
void print_forward_list(std::forward_list<t>& frwd)
{
	cout << endl;
	if (!frwd.empty())
	{
		for (t x : frwd)
			cout << "x = " << x << endl;
	}
	else
	{
		cout << endl << "forward_list is empty" << endl;
	}
}


template<typename t>
void print_forward_list_info(std::forward_list<t>& frwd)
{
	cout << endl;
	cout << "frwd.empty()    " << std::boolalpha << frwd.empty() << endl;
	cout << "frwd.max_size() " << frwd.max_size() << endl;
	cout << "frwd.size()     " << std::distance(frwd.begin(), frwd.end()) << endl;
}



template<typename InputIterator, typename t>
inline InputIterator findBefore(InputIterator first, InputIterator last, const t & val)
{
	if (first == last)
		return first;

	InputIterator next(first);
	++next;
	while ((next != last) && !(*next == val))
	{
		++next;
		++first;
	}
	return first;
}


template <typename InputIterator, typename Pred>
inline InputIterator findBefore_if(InputIterator first, InputIterator last, Pred pred)
{
	if (first == last)
		return first;

	InputIterator next(first);
	++next;
	while ((next != last) && !pred(*next))
	{
		++next;
		++first;
	}
	return first;
}

template <typename InputIterator, typename t>
inline InputIterator findIterator(InputIterator first, InputIterator last, const t & value)
{
	if (first == last)
		return first;
	
	while ( (first != last) && (*first != value) )
		++first;

	return first;
}






//сравнение строк вне зависимости от регистра
bool compare_strings_lower(string  s1, string  s2);

class CompUpper
{
public:
	bool operator()(string  s1, string  s2)
	{
		std::transform(s1.begin(), s1.end(), s1.begin(), toupper);
		std::transform(s2.begin(), s2.end(), s2.begin(), toupper);
	
		if (0 == s1.compare(s2))
			return true;
		else
			return false;
	}
};

bool cmp_abs(int a, int b);


void test_forward_list();

//--------------------------------тестирование множеств std::set<>-----------------------------------------------------------------
template<typename t, typename cmp>
void print_set(std::set<t,cmp> & st)
{
	cout << endl;
	if (!st.empty())
	{
		for (t x : st)
			cout << "x = " << x << endl;
	}
	else
	{
		cout << "set is empty" << endl;
	}
}


template<typename InputIterator, typename t, typename cmp>
void print_set_beg_end(InputIterator beg, InputIterator end, std::set<t,cmp> & st)
{
	if (end != st.end())
		++end;

	for (auto i = beg; i != end; ++i)
		cout << "x = " << (*i) << endl;
}


template<typename t, typename cmp>
void bounds(std::set<t, cmp> & st, t val)
{
	cout << endl;
	cout << "value = " << val << endl;
	cout << "lower_bound() " << *st.lower_bound(val) << endl;
	cout << "upper_bound() " << *st.upper_bound(val) << endl;
	cout << "equal_range()  (" << *st.equal_range(val).first << ") - (" << *st.equal_range(val).second <<")"<< endl;
}






template<typename t, typename cmp>
void print_set_info(std::set<t, cmp> & st)
{
	cout << endl;
	cout << "set.size()      = " << st.size() << endl;
	cout << "set.max_size()  = " << st.max_size() << endl;
	cout << "set.empty()     = " << std::boolalpha << st.empty() << endl;
}

template<typename t, typename cmp>
void print_cmp_criteria(std::set<t, cmp> & st)
{
	cout << "set.key_comp()   = " << st.key_comp() << endl;
	cout << "set.value_comp() = " << st.value_comp() << endl;
}


template<typename _Ty>
std::ostream & operator<<(std::ostream & ostr, std::less<_Ty> & ls )
{
	return ostr << "Compare criteria less<t> means that [ (x0 < x1) == true ]";
}

template<typename _Ty>
std::ostream & operator<<(std::ostream & ostr, std::greater<_Ty> & gr)
{
	return ostr << "Compare criteria greater<t> means that [ (x0 > x1) == true ]";
}



class Num
{
private:
	int a;

public:
	Num(int a) : a(a) {}
	~Num() {}

	int get_a() { return a; }

	bool operator< (Num b)
	{
		return this->a < b.get_a();
	}

};

template<typename t>
struct NumLess
{
	bool operator()( t  a,  t  b) const
	{
		 return a < b;
	}
};


std::ostream & operator<<(std::ostream & os, Num & num);



void test_sets();

//-----------------------------------тестирование мультимножеств std::multiset<>-----------------------------------------------

template<typename t, typename cmp>
void print_multiset(std::multiset<t, cmp> & mset)
{
	cout << endl;
	if (!mset.empty())
	{
		for (t x : mset)
			cout << "x = " << x << endl;
	}
	else
		cout << "Multiset is empty" << endl;
}

void test_multisets();


//------------------------------------------тестирование отображений std::map<>------------------------------------------------
template <typename Key, typename Val, typename Cmp>
void print_map(std::map<Key, Val, Cmp> & mp)
{
	cout << endl;
	if (!mp.empty())
	{
		for (auto x : mp)
			cout << x << endl;
	}
	else
		cout << "Map is empty" << endl;
}



template<typename Key, typename Val, typename Cmp>
void mapbounds(std::map<Key, Val, Cmp>& mp, Key val)
{
	cout << "Map bounds for " << "Val = " << val << endl;

	std::pair<Key, Val> lower_element, upper_element;

	lower_element = *mp.lower_bound(val);
	cout << "map.lower_bound() key1 = " << lower_element.first << endl;

	upper_element = *mp.upper_bound(val);
	cout << "map.upper_bound() key2 = " << upper_element.first  << endl;

	std::pair<std::map<Key,Val,Cmp>::iterator, std::map<Key, Val, Cmp>::iterator> para_its  = mp.equal_range(val);		//функция возвращает пару итераторов std::pair<it1,it2>
	lower_element = *para_its.first;
	upper_element = *para_its.second;

	cout << "map.equal_range() = " <<"[ key1 = "<< lower_element.first << ", key2 = " << upper_element.first <<"]"<< endl;
}

//функция для замены ключа у элемента
template<typename Container>
inline bool replace_key(Container & c, typename Container::key_type & old_key, typename Container::key_type & new_key)
{
	typename Container::iterator pos;

	pos = c.find(old_key);										//ищем элемент со старым ключом	
	if (pos != c.end())
	{
		c.insert(std::make_pair(new_key, pos->second));			//вставляем пару из нового ключа и старого значения
		c.erase(pos);											//удаляем старый элемент
		return true;
	}
	else
		return false;
}


class RealTimeCmp
{
public:
	enum cmp_mode { normal, nocase };
	RealTimeCmp(cmp_mode m = normal) : mode(m) {}

	static bool nocase_compare(char c1, char c2)
	{
		return toupper(c1) < toupper(c2);
	}


	bool operator()(const string & s1, const string & s2)const
	{
		if (mode == normal)
			return s1 < s2;
		else
			return std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), nocase_compare);
	}

private:
	cmp_mode mode;

};




void test_maps();



//---------------тестирование неупорядоченных множеств и мультимножеств std::unorderd_set<> and std::unordered_multiset<>--------

template<typename t, typename hf, typename cmp>
void print_unordered_set(std::unordered_set<t, hf, cmp> & uset)
{
	cout << endl;
	if (!uset.empty())
	{
		for (t x : uset)
			cout << "x = " << x << endl;
	}
	else
		cout << "Unordered_set<t,hf,cmp> is empty" << endl;
}


template<typename t, typename hf, typename cmp>
void print_unordered_set_info(std::unordered_set<t, hf, cmp> & uset)
{
	cout << endl;
	cout << "Количество сегментов                       - " << uset.bucket_count() << endl;
	cout << "Максимальное количество сегментов          - " << uset.max_bucket_count() << endl;
	cout << "Количество элементов                       - " << uset.size() << endl;
	cout << "Максимально возможное количество элементов - " << uset.max_size() << endl;
	cout << "Текущий коэффициент заполнения             - " << uset.load_factor() << endl;
	cout << "Максимальный коэффициент заполнения        - " << uset.max_load_factor() << endl;
}


template <typename t>
std::size_t hashf(t val)
{
	return (std::hash<t>()(val) + 0x9E3779B9);
}

class Customer
{
private:
	string name;
	unsigned int check_sum;

public:
	Customer(string name = "Tom", unsigned int check_sum = 55) :name(name), check_sum(check_sum) {}
	string get_name()const { return name; }
	unsigned int get_check_sum()const { return check_sum; }


	bool operator==(const Customer & c1)const 
	{
		return ( this->check_sum == c1.get_check_sum()) && (this->name.compare(c1.get_name()) == 0 );
	}

};


std::ostream & operator<<(std::ostream & ostr, const Customer & c);




class CustomerHash
{
public:
	std::size_t operator()(const Customer & c)const
	{
		return std::hash<unsigned int>()(c.get_check_sum()) + std::hash<string>()(c.get_name());
	}
};



class CustomerEqual
{
public:
	bool operator()(const Customer & c1, const Customer & c2)const
	{
		return (c1.get_name().compare(c2.get_name()) == 0);
	}
};



void test_unordered_sets();

//-------------------------------------тестирование потоков ввода вывода------------------------------------------------------------

void cin_properties(std::istream & cinth);










void test_ithreads();


































#endif

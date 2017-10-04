#ifndef _STUDY_STL_
#define _STUDY_STL_

#include <stdlib.h>
#include <iostream>

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




using std::cout;
using std::endl;
using std::cin;
using std::string;


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













#endif

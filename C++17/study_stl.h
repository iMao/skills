#ifndef _STUDY_STL_
#define _STUDY_STL_


#include <iostream>

#include <math.h>
#include <string.h>

#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include <array>
#include <initializer_list>
#include <exception>
#include <utility>
#include <tuple>
#include <vector>




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
		return std::make_pair(static_cast<t>(0), static_cast<t>(0));
	else
	{
		t x1 = (-b - sqrt(D)) / 2 * a;
		t x2 = (-b + sqrt(D)) / 2 * a;

		return std::make_pair( x1, x2 );
	}
}


void test_pairs();


//---------------------------------------------тестирование кортежей std::tuple<T1,T2,...Tn> t-----------------------------
void test_tuples();


//---------------------------------------------тестирование контейнера std::vector<>---------------------------------------
void test_vector();






















#endif

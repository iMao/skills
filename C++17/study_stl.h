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


//----------------------------------------------������������ ������� array<>------------------------------------------------------
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


//---------------------------------------------������������ std::pair<T1,T2>p------------------------------------------------------
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


//---------------------------------------------������������ �������� std::tuple<T1,T2,...Tn> t-----------------------------
void test_tuples();


//---------------------------------------------������������ ���������� std::vector<>---------------------------------------
template<typename t>
void print_vector_info(std::vector<t>& vec)
{
	cout << endl;
	cout << "vec.size()     = " << vec.size() << endl;		//������� ���������� ���������
	cout << "vec.max_size() = " << vec.max_size() << endl;	//������������ ���������� ���������
	cout << "vec.capacity() = " << vec.capacity() << endl;	//���������� ��������� ������� �������� ���������� ��� ��������������� ��������� ������
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
	for (auto & e : v)
		cout << "e = " << e << endl;
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






















#endif

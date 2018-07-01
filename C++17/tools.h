#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <stdint.h>
#include <ctime>

#include <iostream>
#include <fstream>

#include <initializer_list>
#include <thread>
#include <string>
#include <vector>
#include <algorithm>

#include <memory>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <queue>
#include <future>
#include <random>
#include <exception>
#include <ratio>
#include <atomic>




using std::cout;
using std::cin;
using std::endl;

using std::vector;
using std::string;
using std::shared_ptr;
using std::shared_ptr;
using std::unique_ptr;


//---------------------------------первый тест (создание потоков, управление)--------------------------------------------
void thfunc();									//функция для простого потока

void thf(int a);

//класс функтор для запуска в отдельном потоке
class background_task
{
	int a;
public:
	background_task() :a(5) {}
	background_task(int a_) :a(a_) {}
	~background_task() {}

	void operator()()
	{
		for (int i = 0; i < a; i++)
			std::cout << "bgtask is working" << std::endl;
	}

};

//класс для безопасного завершения потока
class thread_guard
{
	std::thread & t;

public:
	thread_guard() :t(std::thread([]() {std::cout << "hello thread_guard" << std::endl; })) {}
	thread_guard(std::thread & t_) : t(t_) {}

	~thread_guard()
	{
		if (t.joinable())
			t.join();
		std::cout << "thread safetly joined" << std::endl;
	}

	thread_guard(thread_guard const& t) = delete;
	thread_guard& operator=(thread_guard const & t) = delete;
};

//класс функции-члены которого будут передаваться в потоки
class Xth
{
private:
	int a;
public:
	Xth() :a(2) {}
	Xth(int a_) :a(a_) {}



	void do_some_thing(std::string  str)
	{
		for (int i = 0; i < a; i++)
			std::cout << "class Xth{} " << str << std::endl;
	}

	void clear(int & a_, int & b_, int & c_)
	{
		a_ = 0;
		b_ = 0;
		c_ = 0;
	}


};

enum week
{
	mon, tued, wen
};

class X
{
private:
	int a;

public:
	X() :a(2) {}
	X(int a_) :a(a_) {}

	void increment_2(int & a_, int & b_, int & c_)
	{
		for (int i = 0; i < a; i++)
		{
			a_ += 2;
			b_ += 2;
			c_ += 2;
		}
	}
};

void test_number_1();

//---------------------------------------------------второй тест (передача параметров для функции потока)-------------------------------------------------
void tst_param(int a, float& b, std::string& str, std::string & buf);

void test_number_2();

//---------------------------------------------------тестирование семантики перемещения для объектов std::thread------------------------------------------
void f();												//простая функция потока печатает id потока

void func(std::string & s);

void test_number_3();

//--------------------------------------------------тестирование интеллектуальных указателей--------------------------------------------------------------
void deleter(int *p);

class Deleter
{
public:

	void operator()(int* p)
	{
		cout << endl << "Deleter is working" << endl;

		for (int i = 0; i < 10; i++)
			cout << "\n x = " << p[i];

		delete p;
	}
};

void test_shared_ptr();

class SuperData
{
private:
	int* a;
	int b;
	int c;
public:
	SuperData()
	{
		a = new int;
		*a = 10;

		b = 2;

		c = (*a) / b;
	};

	~SuperData()
	{
		if (a != nullptr)
		{
			delete a;
		}

		b = 0;
		c = 0;

		cout << " All resoures was returned\n";
	}

	void prn()
	{
		cout << "a = " << *a << " b = " << b << " c = " << c << endl;
	}
};

//функтор для реализации стратегии закрытия и удаления файла
class FileDeleter
{
private:
	string filename;

public:
	FileDeleter(string const & fn) :filename(fn) {}

	void operator()(std::ofstream* fp)
	{
		delete fp;
		std::remove(filename.c_str());
		cout << "file " << filename << " was removed \n";
	}
};

void test_intel_ptrs();									//тестирование интелектуальных указателей

void test_intel_ptrs_hard();							//тестирование дополнительных возможностей shared_ptr<>

//----------------------------------------------тестирование уникальных указателей unique_ptr<>---------------------------------------
unique_ptr<string> createString(char const* charArray);	//функция исток

void printString(unique_ptr<string> ps);				//функция сток

class ArrayDeleter
{
public:
	void operator()(int* p)
	{
		cout << "\n You delete array ArrayDeleter()\n";
		delete[] p;
	}
};

void fdeleter(int * p);

void test_unique_ptr();

void test_unique_ptrs();

//----------------------------------------------------тестирование идентификации потоков----------------------------------------------
void some_work();

class ThreadJointer
{
public:
	void operator()(std::thread & t)
	{
		if (t.joinable())
		{
			cout << "\n Thread with id " << t.get_id() << " joined" << endl;
			t.join();
		}
	}
};

void test_threads_id();

//----------------------------------------------------тестиование мьютексов-----------------------------------------------------------
void print_rec(string& s, std::recursive_mutex& mut);

void print(string& s, std::mutex& mut);

int someWorkWhileMutexBusy();

void swap(int & a, int & b);

void test_mutex();

//----------------------------------------------------unique_lock()--------------------------------------------------------------------
void test_unique_lock();

//----------------------------------------------------тестиование condition variables--------------------------------------------------
void insertValue(int & val, std::queue<int> & qu, std::mutex & mut, std::condition_variable & cv);

void getValue(std::queue<int> & qu, std::mutex & mut, std::condition_variable & cv);

void test_condition_variables();

void test_condition_variable_queue();

//---------------------------------------------------тестирование объектов будущих результатов и асинхронного выполнения функций-------
void async_func();

void fill_array(std::vector<int>& vec, int size, int i);

string stringback(string s);						//функция для оборачивания строки

class Xc
{
private:

public:
	Xc() {}
	~Xc() {}

	void print_s(string s)
	{
		cout << s;
	}


	void operator()(string s)
	{
		cout << s;
	}
};

void test_future_and_async();

void test_async_and_future();						//тестирование асинхронного выполнения задач и объектов будущих результатов

//--------------------------------------------------тестирование упакованных задач-----------------------------------------------------
double computeMul(double x, double y);

void test_packaged_task();

//--------------------------------------------------тестирование размеров указателей---------------------------------------------------
void test_pointers_size();

//--------------------------------------------------тестирование библиотечки хроно-----------------------------------------------------
template <typename V, typename R>
std::ostream& operator<<(std::ostream& s, std::chrono::duration<V,R>& d)
{
	s << "[" << d.count() << " of " << R::num << "/" << R::den << "]";
	return s;
}

template<typename C>
void printClockData()
{
	using namespace std;

	cout << endl << "-precision:";

	typedef typename C::period P;

	if (ratio_less_equal<P, milli>::value)
	{
		typedef typename ratio_multiply<P, kilo>::type TT;
		cout << fixed << double(TT::num) / TT::den<<" milliseconds"<<endl;
	}
	else
	{
		cout << fixed << double(P::num) / P::den << " seconds" << endl;
	}

	cout << "-is steady: " << boolalpha << C::is_steady << endl;
}

string timeAsString(std::chrono::system_clock::time_point & tp);

void test_chrono();


//----------------------------------тестирование атомарных операций----------------------------------------------------------------------


template <typename atom_t>
void get_atomic_info(std::atomic<atom_t> & atom_var)
{
	cout << "atomic variable information: " << endl;
	cout << "is_lock_free(): " <<std::boolalpha<< atom_var.is_lock_free() << endl;
	cout << "atomic value:   " << static_cast<atom_t>(atom_var.load()) << endl;
	cout << endl;
}



struct data_Ty {
	int a;
	int b;
	float f;
	string s;

	friend std::ostream& operator<<(std::ostream & os, data_Ty & dty) {
		return os << "a = " << dty.a << " b = " << dty.b << " f = " << dty.f << " s = " << dty.s << endl;
	}

};


void test_atomic();


















#endif

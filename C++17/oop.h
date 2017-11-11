#ifndef _OOP_H_
#define _OOP_H_

#include <iostream>
#include <string>


using std::cout;
using std::wcout;

using std::cin;
using std::wcin;

using std::endl;


using std::string;





//---------------------------------тест ООП---------------------------------------------

class Stock
{
private:
	static int counter;																	//счетчик количества объектов
	std::string company;																//имя компании
	long shares;																		//количество акций
	double share_val;																	//доля 1 акции
	double total_val;																	//общая доля владения

	void set_tot() { total_val = shares * share_val; }

public:
	Stock();																			//конструктор по умолчанию	
	Stock(double total_val);															//конструктор с одним параметром			
	Stock(const std::string & company, long shares = 0, double share_val = 0.0);		//конструктор с несколькими параметрами
	Stock(const Stock & stock);															//конструктор копирования	
	~Stock();																			//деструктор

	std::string getCompany()const	{ return company;   }
	long getShares()const			{ return shares;    }
	double getShareVal()const		{ return share_val; }
	double getTotalVal()const		{ return total_val; }

	void buy(long shares, double price);
	void sell(long shares, double price);
	void show()const;

	static void set_counter(int init_val);												//статическая функция инициализации счетчика объектов			

};





class A {
public:
	std::string s;

	A() :s("Default class A") { std::cout << "Default constructor of class A()" << std::endl; }
	A(std::string s) :s(s)    { std::cout << "Constructor of class A(p)" << std::endl; }
	A(const A& a) :s(a.s)     { std::cout << "Copy constructor of class A(A&)" << std::endl; }
	A(A&& a)                  
	{ 
		s = std::move(a.s);  
		std::cout << "Move constructor of class A(A&&)" << std::endl; 
	}

	~A() { std::cout << "Destructor of class A - " + s << std::endl; }

	void p() { std::cout << "s - " << s << std::endl; }
};





//-------------------------------------наследование------------------------------------------------------------------------------
class Base {
private:
	int i;
	int j;
public:
	Base() { i = 0; j = 0; }
	Base(int i, int j) :i(i), j(j) { std::cout << "Constructor Base" << std::endl; }
	~Base() { std::cout << "Destructor Base" << std::endl; }

	void setij(int a, int b) { i = a; j = b; }
	void showij() { std::cout << "i = " << i << " " << "j = " << j << std::endl; }
};



//наследование с атрибутом доступа public
class OpenBase : public Base
{
private:
	int k;
public:
	OpenBase() :Base(){
		k = 0;
		cout << "Default OpenBase constructor " << endl; 
	}
	
	OpenBase(int i, int j, int k) : Base(i,j), k(k) {
		cout << "OpenBase(p1,p2,p3) constructor " << endl; 
	}
	
	~OpenBase() {
		cout << "Destructor OpenBase" << endl; 
	}

	void setk(int k) { this->k = k; }
	void showk()const { cout << "k = " << k << endl; }
	
};



//наследование с атрибутом доступа private
class PrivateBase : private Base
{
private:
	int m;
public:
	PrivateBase() : Base(),m(0) {
		cout << "Default PrivateBase constructor " << endl;
	}

	PrivateBase(int i, int j, int m) : Base(i, j),m(m) {
		cout << "PrivateBase(p1,p2,p3) constructor " << endl;
	}

	~PrivateBase() {
		cout << "Destructor PrivateBase" << endl;
	}

	void showijm(){
		showij();						//обращение к закрытым функциям-членам базового класса
		cout << "m = " << m << endl;
	}
};



//наследование protected членов класса
class base {
protected:
	string name;
	string surname;

public:
	base() :name("no name"), surname("no surname") { cout << "base default constructor" << endl; }
	base(string name, string surname) :name(name), surname(surname) { cout << "base constructor(p1,p2)" << endl; }
	~base() { cout << "base destructor" << endl; }

	void print()						{ cout << "name: " + name + " " + "surname: " + surname << endl; }
	void set_name(string name)			{ this->name = name; }
	void set_surname(string surname)	{ this->surname = surname; }
};

//открытое наследование класса base с областью protected
class open_base : public base {
private:	
	string full_name;
public:
	open_base() :base() { cout << "open_base default constructor" << endl; }
	~open_base() { cout << "open_base destructor" << endl; }

	string make_fullname() { full_name = name + " " + surname;  return full_name; }
	void print_fullname() { cout << "full name: " + full_name << endl; }
};


//открытое наследование класса open_base с областью protected унаследованной от класса base
class info_base : public open_base {
public:
	info_base() { cout << "info_base default constructor " << endl; }
	~info_base() { cout << "info_base destructor" << endl; }
	
	void show() { cout << "person: " + name + " " + surname << " -> " << endl; }
};

//закрытое наследование класса open_base с областью protected унаследованной от класса base
class close_base : private open_base {
public:
	close_base() :open_base() { cout << "close_base default constructor " << endl; }
	~close_base()			  { cout << "close_base destructor" << endl; }

	void show_all() { 
		cout <<"name: "<< name <<"surname: "<<surname<< endl; 
		make_fullname();
		print_fullname();
	}

};


void test_class();


//--------------------------множественное наследование---------------------------------------------
const double PI{ 3.14 };


class figure {
protected:
	bool visible;
public:
	figure() :visible(true) { cout << "default constructor of class figure" << endl; }
	~figure() { cout << "destructor of class figure" << endl; }

	void setVisible(bool vis) { visible = vis; }
	bool getVisible()const    { return visible; }

	void getStatus()const { cout << "Status: " << (visible == true ? "visible" : "invisible") << endl; }
};





class circle :  public virtual figure
{
protected:	
	double r;
	double s;
	double l;
public:
	circle() : figure(), r(1){ cout << "circle: R = " << r << endl; }
	circle(double r) : figure(), r(r) { cout << "circle: R = " << r << endl; }
	
	~circle() { cout << "destructor of class circle" << endl; }
	
	void calc_s() { s = PI*r*r; }
	void calc_l() { l = 2 * PI*r; }
	void show_circle() { cout << "circle R = " << r << " S = " << s << " L = " << l << endl; }

	
};


class quad :  public virtual figure
{
protected:
	double a;
	double s;
public:
	quad() : figure(), a(1)  { cout << "quad: A = " << a << endl; }
	quad(double a) : figure(), a(a) { cout << "quad: A = " << a << endl; }
	
	~quad() { cout << "destructor of class quad" << endl; }

	void calc_squad() { s = a*a; }
	void show_quad() { cout << "quad: A = " << a << " S = " << s << endl; }
};



class circle_quad : public circle, public quad
{
public:
	circle_quad(double a) : circle(a / 2), quad(a) { cout << "circle_quad: " << "A = " << a << " R = " << a / 2 << endl; }
	~circle_quad() { cout << "destructor of class circle_quad" << endl; }

	
};

void test_multiple_inheritance();

//----------------------предоставление доступа-----------------------------------------------

class basic {
protected:
	int i, j;
public:
	basic():i(0), j(0) { cout << "constructor of class basic" << endl; }
	basic(int i, int j) :i(i), j(j) { cout << "constructor of class basic" << endl; }
	~basic() { cout << "destructor of class basic" << endl; }

	void setij(int i, int j) { this->i = i; this->j = j; }
	void showij()const { cout << "i = " << i << " j = " << j << endl; }
};


class derived : private basic
{
public:
	derived() :basic() { cout << "constructor of class derived" << endl; };
	derived(int i, int j) : basic(i, j) { cout << "constructor of class derived" << endl; }
	~derived() { cout << "destructor of class derived" << endl; }

	//предоставление доступа, закрытые функции члены делаем открытыми
	basic::setij;
	basic::showij;

};




void test_access_declaration();















































#endif

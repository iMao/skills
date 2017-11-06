#include "oop.h"




//-----------------------тест ООП---------------------------------------------

Stock::Stock()
{
	std::cout << "Constructor Stock(){}" << std::endl;

	company = "no name";
	shares = 0;
	share_val = 0.0;
	set_tot();
}

Stock::Stock(const Stock & stock)
{
	std::cout << "Copy constructor Stock(const Stock& stock)" << std::endl;

	this->company   = stock.getCompany();
	this->shares    = stock.getShares();
	this->share_val = stock.getShareVal();
	this->total_val = stock.getTotalVal();
}


Stock::Stock(const std::string & company, long shares, double shares_val)
{
	std::cout << "Constructor Stock(p1,p2,...)" << std::endl;

	this->company = company;
	this->shares = shares;
	this->share_val = shares_val;
	set_tot();
}

Stock::Stock(double total_val)
{
	std::cout << "Constructor Stock(p1)" << std::endl;
	company = "x company";
	shares = 100;
	share_val = total_val / shares;
	this->total_val = total_val;
}



Stock::~Stock()
{
	std::cout << "Destructor ~Stock(){} for object: " <<company<< std::endl;
}


void Stock::buy(long shares, double price)
{
	this->shares += shares;
	this->share_val = price;
	set_tot();
}

void Stock::sell(long shares, double price)
{
	this->shares -= shares;
	this->share_val = price;
	set_tot();
}


void Stock::show()const
{
	std::cout.width(10);
	std::cout.setf(std::ios::uppercase);
	std::cout << std::string("Company: ") + company << std::endl;

	std::cout << "shares: ";
	std::cout.setf(std::ios::showpos);
	std::cout.setf(std::ios::right, std::ios::adjustfield);
	std::cout << shares<<std::endl;

	std::cout << "shares value: ";
	std::cout.setf(std::ios::showpos);
	std::cout.setf(std::ios::right, std::ios::adjustfield);
	std::cout << share_val << std::endl;

	std::cout << "total value: ";
	std::cout.setf(std::ios::showpos);
	std::cout.setf(std::ios::right, std::ios::adjustfield);
	std::cout << total_val << std::endl;

	std::cout << "--------------------------------------------------" << std::endl;
}




void test_class()
{

	std::cout << "tests oop:" << std::endl;
	{
		Stock stock1;							//неявный вызов конструктора по умолчанию
		Stock stock2 = Stock();					//явный вызов конструктора по умолчанию
		Stock stock3(stock1);					//явный вызов конструктора копирования
		Stock stock4("Morgan Stanly");			//неявный вызов конструктора с параметрами
		Stock stock5 = Stock("GP Morgan");		//явный вызов конструктора с параметрами
		Stock stock6 = Stock("IBM", 100, 15.5);
		Stock stock7("Microsoft", 45, 10.0);
		Stock stock8{ "BP", 150, 67.2 };		//создание объекта при помощи списка инициализации	
		Stock stock9 = 92.0;					//вызов конструктора с одним параметром	
		Stock stock10{ 67.5 };


		stock1.show();
		stock2.show();
		stock3.show();
		stock4.show();
		stock5.show();
		stock6.show();
		stock7.show();
		stock8.show();
		stock9.show();
		stock10.show();
	}
}

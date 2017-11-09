#include "oop.h"




//-----------------------���� ���---------------------------------------------
int Stock::counter;			//����������� ������������ ���� ������


Stock::Stock()
{
	std::cout << "Constructor Stock(){}" << ++counter << std::endl;

	company = "no name";
	shares = 0;
	share_val = 0.0;
	set_tot();
}

Stock::Stock(const Stock & stock)
{
	std::cout << "Copy constructor Stock(const Stock& stock)" << ++counter <<  std::endl;

	this->company   = stock.getCompany();
	this->shares    = stock.getShares();
	this->share_val = stock.getShareVal();
	this->total_val = stock.getTotalVal();
}


Stock::Stock(const std::string & company, long shares, double shares_val)
{
	std::cout << "Constructor Stock(p1,p2,...)" << ++counter << std::endl;

	this->company = company;
	this->shares = shares;
	this->share_val = shares_val;
	set_tot();
}

Stock::Stock(double total_val)
{
	std::cout << "Constructor Stock(p1)" << ++counter  << std::endl;
	company = "x company";
	shares = 100;
	share_val = total_val / shares;
	this->total_val = total_val;
}






Stock::~Stock()
{
	std::cout << "Destructor ~Stock(){} for object: " << counter-- <<"  "<<company<< std::endl;
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


void Stock::set_counter(int init_val)
{
	counter = init_val;
}


void test_class()
{

	std::cout << "tests oop:" << std::endl;
	{
		Stock::set_counter(500);						//��������� ���������� �������� ��� ������������ ���� id

		Stock stock1;							//������� ����� ������������ �� ���������
		Stock stock2 = Stock();					//����� ����� ������������ �� ���������
		Stock stock3(stock1);					//����� ����� ������������ �����������
		Stock stock4("Morgan Stanly");			//������� ����� ������������ � �����������
		Stock stock5 = Stock("GP Morgan");		//����� ����� ������������ � �����������
		Stock stock6 = Stock("IBM", 100, 15.5);
		Stock stock7("Microsoft", 45, 10.0);
		Stock stock8{ "BP", 150, 67.2 };		//�������� ������� ��� ������ ������ �������������	
		Stock stock9 = 92.0;					//����� ������������ � ����� ����������	
		Stock stock10{ 67.5 };
		Stock stock11 = Stock(55.2);

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
		stock11.show();
	}

	std::cout << std::endl << "Work with constructs:" << std::endl;
	std::cout << std::endl;
	{
		A a1;
		A a2("This is a2");
		A a3(a1);
		A a4(std::move(a2));

		a1.p();
		a2.p();
		a3.p();
		a4.p();
	}



	cout << endl << "class inheritance" <<endl;
	{
		cout << endl << "object of class Base" << endl;
		Base b(1, 2);
		b.showij();


		cout << endl << "object of class OpenBase" << endl;
		OpenBase ob(3,5,6);
		ob.setk(10);
		ob.showij();
		ob.showk();

		cout << endl << "object of class PrivateBase" << endl;
		PrivateBase pb(7, 7, 8);
		pb.showijm();
	}
}
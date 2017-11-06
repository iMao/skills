#ifndef _OOP_H_
#define _OOP_H_

#include <iostream>
#include <string>

//---------------------------------тест ООП---------------------------------------------

class Stock
{
private:
	std::string company;						//имя компании
	long shares;								//количество акций
	double share_val;							//доля 1 акции
	double total_val;							//общая доля владения

	void set_tot() { total_val = shares * share_val; }

public:
	Stock();
	Stock(const Stock & stock);
	Stock(const std::string & company, long shares = 0, double share_val = 0.0);
	Stock(double total_val);
	~Stock();

	std::string getCompany()const	{ return company;   }
	long getShares()const			{ return shares;    }
	double getShareVal()const		{ return share_val; }
	double getTotalVal()const		{ return total_val; }



	void buy(long shares, double price);
	void sell(long shares, double price);
	void show()const;
};




void test_class();





























#endif

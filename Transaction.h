#ifndef  TRANSACTION_H
#define TRANSACTION_H
#pragma warning(disable: 4996)
#include <string.h>
class Account;

class Transaction
{
public:
	Transaction(Account* s, Account* d, double amount, const char* date);
	Transaction(const Transaction& other);

public:
	void		SetSource(Account* src);
	void		SetDes(Account* dst);
	void		SetAmount(double amount);
	void		SetDate(const char* date);
	Account* GetSource() const;
	Account* GetDes()const;
	double		GetAmount() const;
	char* GetDate() const;

private:
	Account* m_source;
	Account* m_destination;
	double		m_amount;
	char* m_date;
};




#endif // ! TRANSACTION_H


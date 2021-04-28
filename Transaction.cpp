#include "Transaction.h"

Transaction::Transaction(Account* s, Account* d, double amount, const char* date)
{
	SetSource(s);
	SetDes(d);
	SetAmount(amount);
	SetDate(date);
}

Transaction::Transaction(const Transaction& other)
{
	SetDate(other.GetDate());
	this->m_destination = other.GetDes();
	this->m_source = other.GetSource();
	this->m_amount = other.m_amount;
}

void Transaction::SetSource(Account* src)
{
	this->m_source = src;
}

void Transaction::SetDes(Account* dst)
{
	this->m_destination = dst;
}

void Transaction::SetAmount(double amount)
{
	this->m_amount = amount;
}

void Transaction::SetDate(const char* date)
{
this->m_date = new char[strlen(date) + 1];
	strcpy(this->m_date, date); 
}

Account* Transaction::GetSource() const
{
	return this->m_destination;
}

Account* Transaction::GetDes() const
{
	return nullptr;
}

double Transaction::GetAmount() const
{
	return this->m_amount;
}

char* Transaction::GetDate() const
{
	 return this->m_date; 
}

#include "Account.h"

Account::Account()
{
	this->m_balance = 0;
	this->m_accountNumber = 0;
	this->m_totalPersons = 0;
	this->m_persons = nullptr;
	this->m_numberOfTransaction = 0;
	this->m_transactionList = nullptr;
}

Account::Account(Person** persons, int count, double balance)
{
	SetPersons(persons, count);
	SetBalance(balance);
	this->m_accountNumber = persons[0]->GetId() % 1000;
}

Account::Account(const Person& person, double balance)
{
	this->m_transactionList = nullptr;
	this->m_numberOfTransaction = 0;
	this->m_balance = balance;
	this->m_persons = new Person * [1];
	this->m_persons[0] = new Person(person);
	this->m_totalPersons = 1;
	this->m_accountNumber = m_persons[0]->GetId();
}

Account::Account(const Account& other)
{
	this->m_balance = other.m_balance;
	this->m_transactionList = nullptr;
	this->m_persons = nullptr;
	this->m_accountNumber = other.m_accountNumber;
	this->m_totalPersons = other.m_totalPersons;
	this->m_numberOfTransaction = other.m_numberOfTransaction;
	if (other.m_totalPersons != 0) {
		this->m_persons = new Person * [other.m_totalPersons];
		for (int i = 0; i < m_totalPersons; ++i) {
			this->m_persons[i] = new Person(*other.m_persons[i]);
		}
	}
	if (other.m_numberOfTransaction != 0)
	{
		this->m_transactionList = new Transaction * [other.m_numberOfTransaction];
		for (int j = 0; j < m_numberOfTransaction; ++j) {
			this->m_transactionList[j] = new Transaction(*other.m_transactionList[j]);
		}

	}
}

Account::~Account()
{
	this->clearTransactions();
	this->clearPersons();
}

void Account::SetPersons(Person** persons, int count)
{
	this->m_totalPersons = count;
	this->m_persons = new Person* [count];
	for(int i = 0 ; i < count ; i++){
		m_persons[i] = new Person(*(persons[i]));
	}
	
}

void Account::SetAccountNumber(int number)
{
	this->m_accountNumber = number;
}

void Account::SetBalance(double balance)
{
	this->m_balance = balance;
}

void Account::SetTransactions(Transaction** newTransaction, int count)
{
	this-> m_transactionList = new Transaction * [count];
	if(this->m_transactionList != NULL)
		for (int i = 0; i < count; i++) {
			this->m_transactionList[i] = new Transaction(*(newTransaction[i]));
		}
}

Transaction** Account::GetTransactions()
{
	return this->m_transactionList;
}

int Account::GetNumOfTransactions()
{
	return this->m_numberOfTransaction;
}

Person** Account::GetPersons() const
{
	return this->m_persons;
}

int Account::GetTotalPersons() const
{
	return this->m_totalPersons;
}

int Account::GetAccountNumber() const
{
	return this->m_accountNumber;
}

double Account::GetBalance() const
{
	return this->m_balance;
}

void Account::Withdraw(double amount, const char* date)
{
	Transaction* newTransaction = new Transaction(this, this, amount, date);
	AddTransaction(*newTransaction);
	this->m_balance -= amount;
}

void Account::Deposit(double amount, const char* date)
{
	Transaction* newTransaction = new Transaction(this, this, amount, date);
	AddTransaction(*newTransaction);
	this->m_balance += amount;
}

void Account::AddPerson(const Person& newPerson, double amount)
{
	if (m_totalPersons <= 0) {
		this->m_persons = new Person*[1];
		this->m_persons[0] = new Person(newPerson);
	}
	else
	{
		for (int i = 0; i < m_totalPersons; i++) {
			if(m_totalPersons!=0)
				if (newPerson.GetId() == m_persons[i]->GetId())
					return;
		}
		Person** tempArr = new Person * [m_totalPersons + 1];
		for (int i = 0; i < m_totalPersons; i++)
			tempArr[i] = this->m_persons[i];
		delete[] m_persons;
		this->m_persons = tempArr;
		this->m_persons[m_totalPersons] = new Person(newPerson);
	}
	this->m_balance += amount;	
	this->m_totalPersons++;
}	


void Account::DeletePerson(const Person& oldPerson)
{
	for(int i = 0 ; i < m_totalPersons;i++)
		if (m_persons[i]->GetId() == oldPerson.GetId()) {
			m_persons[i]->~Person();
		}
	m_totalPersons--;
	if (m_totalPersons <= 0)
		delete[] m_persons;
}

void Account::AddTransaction(const Transaction& newTransaction)
{
	if (this->m_transactionList == nullptr)
	{
		this->m_transactionList = new Transaction * [1];
		this->m_transactionList[0] = new Transaction(newTransaction);
		this->m_numberOfTransaction++;

		if (newTransaction.GetSource() != newTransaction.GetDes())
		{
			if (newTransaction.GetSource()->GetAccountNumber() != this->GetAccountNumber()) {
				newTransaction.GetSource()->m_numberOfTransaction++;
			}
			if (newTransaction.GetDes()->GetAccountNumber() != this->GetAccountNumber()) {
				newTransaction.GetDes()->m_numberOfTransaction++;
			}
			newTransaction.GetDes()->SetBalance(newTransaction.GetDes()->GetBalance() + newTransaction.GetAmount());
			newTransaction.GetSource()->SetBalance(newTransaction.GetSource()->GetBalance() - newTransaction.GetAmount());
		}
		return;
	}
	Transaction** temp = new Transaction * [m_numberOfTransaction + 1];
	for (int i = 0; i < this->m_numberOfTransaction; ++i) {
		temp[i] = this->m_transactionList[i];
	}
	temp[m_numberOfTransaction] = new Transaction(newTransaction);
	this->m_transactionList = new Transaction * [m_numberOfTransaction];
	for (int i = 0; i < m_numberOfTransaction; ++i) {
		this->m_transactionList[i] = temp[i];
	}
	if (newTransaction.GetSource() != newTransaction.GetDes())
	{
		newTransaction.GetDes()->m_numberOfTransaction++;
		newTransaction.GetDes()->SetBalance(newTransaction.GetDes()->GetBalance() + newTransaction.GetAmount());
		newTransaction.GetSource()->SetBalance(newTransaction.GetSource()->GetBalance() - newTransaction.GetAmount());
	}
	this->m_numberOfTransaction++;
	
}

void Account::clearTransactions()
{

	for (int i = 0; i < m_numberOfTransaction; i++)
		if(this->m_transactionList[i] != nullptr)
			delete m_transactionList[i];
	delete[] m_transactionList;
	
	if(this->m_transactionList != NULL)
		this-> m_numberOfTransaction = 0;
}


void Account::clearPersons()
{
	if(m_totalPersons>0)
		if (this-> m_persons != NULL) {
			for (int i = 0; i < m_totalPersons; i++)
				delete this-> m_persons[i];
			delete[] this-> m_persons;
		}
	m_totalPersons = 0;
}

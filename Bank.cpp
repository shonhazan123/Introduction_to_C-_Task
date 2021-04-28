#include "Bank.h"
#pragma warning(disable: 4996)
Bank::Bank(const char* name, int code)
{
	SetBankName(name); 
	SetCode(code);
}
Bank::~Bank()
{
	
}
void Bank::SetBankName(const char* name)
{
	m_name = new char[strlen(name)];
	strcpy(m_name, name);
}
void Bank::SetAccount(Account** account, int numbeOfAccounts)
{
	m_account = new Account * [m_numbeOfAccounts];
	for (int i = 0; i < m_numbeOfAccounts; i++)
		m_account[i] = new Account(*account[i]);
}

void Bank::SetTotal(double total)
{
	m_totalBalance = total;
}

void Bank::SetCode(int code)
{
	 m_bankCode = code; 
}

const char* Bank::GetBankName() const
{
	return m_name;
}

Account** Bank::GetAccounts() const
{
	return m_account;
}

int Bank::GetNumberOfAccounts() const
{
	return m_numbeOfAccounts;
}

double Bank::GetTotal() const
{
	return m_totalBalance;
}

int Bank::GetCode() const
{
	return m_bankCode;
}

void Bank::AddAccount(const Account& account)
{
	for (int i = 0; i < m_numbeOfAccounts; i++)
		if (m_account[i]->GetAccountNumber() == account.GetAccountNumber())
			return;
	if (m_numbeOfAccounts <= 0) {
		m_account = new Account * [2];
		m_account[0] = new Account(account);
	}
	else
	{
		Account** tempAcounts = new Account * [m_numbeOfAccounts + 1];
		for (int i = 0; i < m_numbeOfAccounts; i++)
			tempAcounts[i] = m_account[i];
		delete[] m_account;
		m_account = tempAcounts;
		m_account[m_numbeOfAccounts] = new Account(account);
	}
	m_numbeOfAccounts++;
	m_totalBalance += account.GetBalance();
}

void Bank::AddAccount(const Person& per, double amount)
{
	
	Account** tempAcc = new Account * [m_numbeOfAccounts+1];
	for (int i = 0; i < m_numbeOfAccounts; i++)
		tempAcc[i] = m_account[i];
	delete[] m_account;
	m_account = tempAcc;
	m_account[m_numbeOfAccounts] = new Account(per, amount);
	m_numbeOfAccounts++;
	m_totalBalance += amount;

}

void Bank::AddPerson(const Person& newPerson, const Account& account, double amount)
{
	
	for (int i = 0; i < m_numbeOfAccounts; i++) {
		if (m_account[i]->GetAccountNumber() == account.GetAccountNumber()) {
			Person** tempPerson = new Person*[m_account[i]->GetTotalPersons()];
			tempPerson = this->m_account[i]->GetPersons();
			for (int j = 0; j < m_account[i]->GetTotalPersons(); j++) {
				if (tempPerson[j]->GetId() == newPerson.GetId())
					return;
				else
				{
					m_account[i]->AddPerson(newPerson, amount);
					m_totalBalance += amount;
					return;
				}
			}
				

		}
	}
}

void Bank::DeleteAccount(const Account& account)
{
	for(int i = 0 ; i < m_numbeOfAccounts; i++)
		if (m_account[i]->GetAccountNumber() == account.GetAccountNumber()) {
			m_totalBalance -= account.GetBalance();
			delete m_account[i];
			m_numbeOfAccounts--;
		}
	delete[] m_account;
}

void Bank::DeletePerson(const Person& p)
{
	for (int i = 0; i < m_numbeOfAccounts; i++) {
		for (int j = 0; j < m_account[i]->GetTotalPersons(); j++)
			if (m_account[i]->GetPersons()[j]->GetId() == p.GetId()) {
				m_account[i]->DeletePerson(p);
				if (m_account[i]->GetTotalPersons() <= 0)
					DeleteAccount(*m_account[i]);
				return;
			}
			
	}
}

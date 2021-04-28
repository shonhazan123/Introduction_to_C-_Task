#include "Transaction.h"
#include "Person.h"
#pragma warning(disable: 4996)

Person::Person(const char* name, int id)
{
	SetName(name);
	SetId(id);
}

Person::Person(const Person& other)
{
	SetName(other.GetName());
	this->m_id = other.GetId();
}

Person::~Person()
{
	delete this-> m_name;
}

void Person::SetName(const char* newName)
{
	this-> m_name = new char[strlen(newName) + 1];
	strcpy(this->m_name, newName);
}

void Person::SetId(int newId)
{
	this->m_id = newId;
}

char* Person::GetName() const
{
	return this->m_name;
}

int Person::GetId() const
{
	return this->m_id;
}

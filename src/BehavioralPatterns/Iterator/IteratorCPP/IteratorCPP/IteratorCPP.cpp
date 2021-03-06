#include "stdafx.h"

using namespace std;

//Интерфейс итератора
template <typename T>
class IIterator
{
public:
	typedef T value_type;
	virtual bool HasNext() = 0;
	virtual T Next() = 0;
};

//обьект с которым будет работать итератор
class NameManager
{
public:
	typedef vector<string> NameCollection;
	NameCollection names;

	//класс конкретного итератора
	class NameIterator : public virtual IIterator<NameCollection::value_type>
	{
	public:
		NameManager::NameCollection &names;
		NameManager::NameCollection::iterator itr;

		NameIterator(NameManager::NameCollection &namesColl) : names(namesColl), itr(names.begin()) {}

	public:
		virtual bool HasNext() override { return itr != names.end(); }
		virtual NameIterator::value_type Next() override
		{
			NameIterator::value_type value = (*itr);
			++itr;
			return value;
		}
	};

	//продолжение класса с которым будет работать итератор
	void AddName(NameCollection::value_type name) { names.push_back(name); }
	NameIterator GetNameIterator() { return NameIterator(names); }
};

int main()
{
	system("color 70");
	setlocale(0, "");
	SetConsoleTitle(TEXT("Iterator"));

	NameManager nm;

	nm.AddName("Bill");
	nm.AddName("Jhon");
	nm.AddName("Pitter");
	nm.AddName("Mary");
	nm.AddName("Jhohana");

	NameManager::NameIterator itr = nm.GetNameIterator();

	while (itr.HasNext())
	{
		cout << itr.Next() << endl;
	}

	system("pause");

    return 0;
}


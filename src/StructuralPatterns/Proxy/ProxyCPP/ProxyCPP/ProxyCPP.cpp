#include "stdafx.h"

using namespace std;

//Интерфейс обьекта
class IMath
{
public:
	virtual ~IMath() {};

	virtual int Sum(int a, int b) = 0;
};

//Сам обьект
class Math : virtual public IMath
{
public:
	virtual int Sum(int a, int b) override
	{
		return a + b;
	}
};

//Прокси для обьекта
class ProxyMath : virtual public IMath
{
private:
	IMath * math;

public:
	ProxyMath()
	{
		math = new Math();
	}
	~ProxyMath()
	{
		delete math;
	}

	virtual int Sum(int a, int b) override
	{
		return math->Sum(a, b);
	}
};

int main()
{
	system("color 70");
	setlocale(0, "");
	SetConsoleTitle(TEXT("Proxy"));

	IMath * p = new ProxyMath();

	cout << p->Sum(1, 5) << endl;

	delete p;

	system("pause");
    return 0;
}


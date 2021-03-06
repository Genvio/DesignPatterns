#include "stdafx.h"

using namespace std;

//Обстарктный класс, общий для данного продукта
class Pizza
{
private:
	string dough;		//тесто
	string sauce;		//соус
	string topping;		//"начинка"

public:
	Pizza() {}
	virtual ~Pizza() {}

	void SetDough(const string& d) { dough = d; }
	void SetSause(const string& s) { sauce = s; }
	void SetTopping(const string& t) { topping = t; }

	void DescribePizza()
	{
		cout << "Pizza!" << endl
			<< "With Dough as " << dough
			<< ", Sause as " << sauce
			<< " and Topping as " << topping
			<< "." << endl;
	}
};

//Абстрактный билдер для любого продукта
class PizzaBuilder
{
protected:
	shared_ptr<Pizza> pizza;

public:
	PizzaBuilder() {}
	virtual ~PizzaBuilder() {}

	shared_ptr<Pizza> GetPizza() { return pizza; }
	void CreateNewPizza() { pizza.reset(new Pizza); }

	virtual void BuildDough() = 0;
	virtual void BuildSause() = 0;
	virtual void BuildTopping() = 0;
};

//Класс конкретного продукта
class HawaiianPizzaBuilder : virtual public PizzaBuilder
{
public:
	HawaiianPizzaBuilder() {}
	virtual ~HawaiianPizzaBuilder() {}

	virtual void BuildDough() override { pizza->SetDough("cross"); }
	virtual void BuildSause() override { pizza->SetSause("hot"); }
	virtual void BuildTopping() override { pizza->SetTopping("pepperoni and salami"); }
};

//Класс конктретного продукта
class SpicyPizzaBuilder : virtual public PizzaBuilder
{
public:
	SpicyPizzaBuilder() {}
	virtual ~SpicyPizzaBuilder() {}

	virtual void BuildDough() override { pizza->SetDough("pan baked"); }
	virtual void BuildSause() override { pizza->SetSause("mild"); }
	virtual void BuildTopping() override { pizza->SetTopping("ham and pineapple"); }
};

//Руководитель создания продуктов
class Director
{
private:
	PizzaBuilder * builder;

public:
	Director() : builder(NULL) {}
	~Director() {}

	void SetPizzaBuilder(PizzaBuilder * b) { builder = b; }
	shared_ptr<Pizza> GetPizza() { return builder->GetPizza(); }

	void CreatePizza()
	{
		builder->CreateNewPizza();

		builder->BuildDough();
		builder->BuildSause();
		builder->BuildTopping();
	}
};

int main()
{
	system("color 70");
	setlocale(0, "");
	SetConsoleTitle(TEXT("Builder"));

	Director director;

	shared_ptr<Pizza> pizza;

	//Билдеры конкретных продуктов
	HawaiianPizzaBuilder hawaiian;
	SpicyPizzaBuilder spicy;

	//создаем конкертный продукт
	director.SetPizzaBuilder(&hawaiian);
	director.CreatePizza();
	pizza = director.GetPizza();

	pizza->DescribePizza();

	//создаем конкертный продукт
	director.SetPizzaBuilder(&spicy);
	director.CreatePizza();
	pizza = director.GetPizza();

	pizza->DescribePizza();

	system("pause");
	return 0;
}


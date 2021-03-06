#include "stdafx.h"

using namespace std;

class Shape;

//Посетитель
class Visitor
{
public:
	void Visit(Shape &ts) { cout << "Visit a Shape" << endl; }
};

//Элемент котрый будут посещать
class Shape
{
public:
	void Draw() { cout << "Drawing a simple shape" << endl; }
	void Accept(Visitor &v) { v.Visit(*this); }
};

int main()
{
	system("color 70");
	setlocale(0, "");
	SetConsoleTitle(TEXT("Visitor"));

	Shape s;
	Visitor v;

	s.Accept(v);

	system("pause");
    return 0;
}


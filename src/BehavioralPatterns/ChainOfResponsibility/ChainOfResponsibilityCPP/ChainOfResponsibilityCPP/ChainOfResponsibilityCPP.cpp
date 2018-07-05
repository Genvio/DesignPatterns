#include "stdafx.h"

using namespace std;

//Обьекты которые будут обрабатываться
class CriminalAction
{
public:
	typedef list<CriminalAction *> CriminalActions;
	string Description;
	int Complexity;

	CriminalAction(int c, string d) : Complexity(c), Description(d) {}
};

//Обьект который будет проводить обработку
class Policeman
{
public:
	CriminalAction::CriminalActions criminalActions;
	string Name;
	int Deduction;

	Policeman(string n, int d) : Name(n), Deduction(d) {}

	void SetCriminalAction(CriminalAction * c)
	{
		criminalActions.push_back(c);
	}

	//Вывод информации по делам полицая, если они есть
	//Пишет, что работник свободен если дел у него нет
	void GetCriminalActions()
	{
		if (criminalActions.size() == 0)
		{
			cout << Name << " is free now" << endl;
			return;
		}

		cout << "Policeman " << Name << " now investigate:" << endl;

		for (auto * a : criminalActions)
			cout << "\t" << a->Description << endl;
	}

	//Работает ли полицай над этим делом
	bool IsOwner(CriminalAction* a)
	{
		auto p = find(criminalActions.begin(), criminalActions.end(), a);

		return p != criminalActions.end();
	}
};


//Обьект который и будет производить обработку дел и передавать их
//в зависимоти от сложности дела полицейским с подходящим опытом
class PoliceDepartment
{
private:
	list<CriminalAction*> criminalActions;
	list<Policeman*> policemans;

public:
	string DepartmentName;

	PoliceDepartment(string dp) : DepartmentName(dp) {}
	~PoliceDepartment()
	{
		for (auto const& a : criminalActions)
			delete a;

		for (auto const& p : policemans)
			delete p;
	}

	//показания статистики, у какого полицая какие дела
	void GetStatistic()
	{
		for (auto const& p : policemans)
		{
			p->GetCriminalActions();
			cout << endl;
		}
	}

	//Получение статистики по делам, описание и сколлько полицаем
	//над ним рабутает
	void GetCriminalActionDetail()
	{
		for (auto * a: criminalActions)
		{
			int pCount = 0;

			for (auto * p : policemans)
				if (p->IsOwner(a))
					pCount++;

			cout << "Criminal action: '" << a->Description << "', Policemans are investigations: " << pCount << endl;
		}
	}

	//при добавлении нового полицая ему присваивается одно или несколько дел
	//в зависимости от его опытности и сложности дела
	void PushNewPoliceman(Policeman* p)
	{
		policemans.push_back(p);

		for (auto * a : criminalActions)
		{
			if (p->Deduction >= a->Complexity)
				p->SetCriminalAction(a);
		}
	}

	//При добавлении дела оно присваивается одному или нескольким
	//полицаям в зависимости от сложности и опытности
	void PushNewCriminalAction(CriminalAction* c)
	{
		criminalActions.push_back(c);

		for (auto * a : policemans)
		{
			if (a->Deduction >= c->Complexity)
				a->SetCriminalAction(c);
		}
	}
};

int main()
{
	system("color 70");
	setlocale(0, "");
	SetConsoleTitle(TEXT("Chain of responsibility"));

	PoliceDepartment *dp = new PoliceDepartment("NYPD");

	dp->PushNewPoliceman(new Policeman("Mark Bufallo", 6));
	dp->PushNewPoliceman(new Policeman("Sam Ivanlovich", 2));
	dp->PushNewPoliceman(new Policeman("Petr Mahno", 7));
	dp->PushNewPoliceman(new Policeman("Simona Richardson", 3));

	dp->PushNewCriminalAction(new CriminalAction(12, "Kill the President"));
	dp->PushNewCriminalAction(new CriminalAction(3, "Steal food"));
	dp->PushNewCriminalAction(new CriminalAction(5, "Steal money"));
	dp->PushNewCriminalAction(new CriminalAction(4, "Steal money in subway"));
	dp->PushNewCriminalAction(new CriminalAction(6, "Kill a dog"));
	dp->PushNewCriminalAction(new CriminalAction(6, "Kill a cat"));
	dp->PushNewCriminalAction(new CriminalAction(7, "Steal money from the bank"));
	dp->PushNewCriminalAction(new CriminalAction(4, "Hit a woman on the street"));
	dp->PushNewCriminalAction(new CriminalAction(6, "Hit a teenagers on the park"));
	dp->PushNewCriminalAction(new CriminalAction(3, "Steal a pet"));

	cout << "Policemant statistic:" << endl;
	dp->GetStatistic();

	cout << "\n\n\nCriminal action statistic:" << endl;
	dp->GetCriminalActionDetail();

	delete dp;

	system("pause");
	return 0;
}


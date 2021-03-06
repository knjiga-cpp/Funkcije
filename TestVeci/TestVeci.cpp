#include <iostream>
using namespace std;

struct Osoba
{
	Osoba(int brojGodina, string ime)
		: BrojGodina(brojGodina)
		, Ime(ime)
	{
	}

	Osoba(const Osoba& o)
		: BrojGodina(o.BrojGodina)
		, Ime(o.Ime)
	{
	}

	int BrojGodina;
	string Ime;
};

bool operator>(const Osoba& o1, const Osoba& o2)
{
	return o1.BrojGodina > o2.BrojGodina;
}

struct Zivotinja
{
	Zivotinja(int brojGodina, string ime)
		: BrojGodina(brojGodina)
		, Ime(ime)
	{
	}

	Zivotinja(const Zivotinja& o)
		: BrojGodina(o.BrojGodina)
		, Ime(o.Ime)
	{
	}

	Zivotinja(const Osoba& o)
		: BrojGodina(o.BrojGodina)
		, Ime(o.Ime)
	{
	}

	int BrojGodina;
	string Ime;
};

bool operator>(const Osoba& o, const Zivotinja& z)
{
	return o.BrojGodina > z.BrojGodina;
}


template <typename Tip1, typename Tip2>
decltype(auto) Veci(Tip1& a, Tip2& b)
{
	return a > b ? a : b;
}


int main()
{
	int a = 5;
	int b = 7;
	int& ab = Veci(a, b);
	++ab;

	//double c = 10;
	//int& ac = Veci(a, c);
	//++ac;

	Osoba o1{ 10, "Dora" };
	Osoba o2{ 7, "Matej" };

	auto& veci = Veci(o1, o2);

	Zivotinja z{ 100, "slon" };
	cin >> z.BrojGodina;
	auto vece = Veci(o1, z);

	return 0;
}


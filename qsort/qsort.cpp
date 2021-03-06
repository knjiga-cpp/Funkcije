#include <cstdlib>        // sadrži definiciju qsort()
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Osoba
{
	string ime;
	int dob;
};

// funkcija usporedbe osoba
int UsporedbaOsoba(const void* o1, const void* o2)
{
	const Osoba* pOsoba1 = static_cast<const Osoba*>(o1);
	const Osoba* pOsoba2 = static_cast<const Osoba*>(o2);
	// ako su dobi različite, vrati razliku dobi...
	if (pOsoba1->dob != pOsoba2->dob)
		return pOsoba2->dob - pOsoba1->dob;
	// ...inače, vrati rezultat usporedbe imena:
	return pOsoba1->ime.compare(pOsoba2->ime);
}

int main()
{
	vector<Osoba> osobe{ { "Dora", 23 },  { "Igor", 45 }, { "Maja", 23 },
						 { "Darko", 23 }, { "Maja", 37 } };

	qsort(osobe.data(), osobe.size(), sizeof(Osoba), UsporedbaOsoba);
	// ispišimo osobe nakon sortiranja:
	for (const auto& o : osobe)
		cout << o.ime << " " << o.dob << endl;
	return 0;
}


#include <iostream>

#include <string>

using namespace std;

std::string imePrograma{"Potapanje brodova"};

std::string& DajReferencuNaIme()
{
	return imePrograma;
}

std::string* DajPokazivacNaIme()
{
	return &imePrograma;
}

struct Osoba
{
	std::string ime;
	std::string prezime;
};

Osoba* DajOsobu(int oib)
{
	switch (oib)
	{
	case 1:
		return new Osoba{ "Dora", "Krupić" };
	case 2:
		return new Osoba{ "Šegrt", "Hlapić" };
	default:
		return nullptr;
	}
}

char* SpojiUDevu0(const char* prvi, const char* drugi)
{
	char spojeni[80];               // lokalni niz znakova
	char* indeks = spojeni;
	if (prvi)                       // da nije nullptr?
	{
		*(indeks++) = toupper(*(prvi++));   // prvo slovo u veliko
		while (*prvi)
			*(indeks++) = *(prvi++);
	}
	if (drugi)                      // da nije nullptr?
	{
		*(indeks++) = toupper(*(drugi++));   // prvo slovo u veliko
		while (*drugi)
			*(indeks++) = *(drugi++);
	}
	*indeks = '\0';
	return spojeni;        // pogreška: vraćamo adresu lokalnog objekta
}

void SpojiUDevu(const char* prvi, const char* drugi, char* spojeni)
{
	char* indeks = spojeni;
	if (prvi)                       // da nije nullptr?
	{
		*(indeks++) = toupper(*(prvi++));   // prvo slovo u veliko
		while (*prvi)
			*(indeks++) = *(prvi++);
	}
	if (drugi)                      // da nije nullptr?
	{
		*(indeks++) = toupper(*(drugi++));   // prvo slovo u veliko
		while (*drugi)
			*(indeks++) = *(drugi++);
	}
	*indeks = '\0';
}

string SpojiUDevu(const char* prvi, const char* drugi)
{
	string spojeni{ prvi };
	if (!spojeni.empty())
		spojeni[0] = toupper(spojeni[0]);
	string nastavak{ drugi };
	if (!nastavak.empty())
		nastavak[0] = toupper(nastavak[0]);
	return spojeni.append(nastavak);
}

int main()
{
	char spojeni[80];
	SpojiUDevu("pero", "laki", spojeni);
	const auto& rez = SpojiUDevu("pero", "laki");
	cout << DajReferencuNaIme() << endl;
	cout << *DajPokazivacNaIme() << endl;

	auto osoba = DajOsobu(2);

	return 0;
}

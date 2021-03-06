#include <iostream>

using namespace std;

//void KapitalizirajPrviZnak(const char* tekst)
//{
//	if (tekst)
//		tekst[0] = toupper(tekst[0]);
//}

void ZamijeniTekst(const char* tekst)
{
	if (!tekst)
		tekst = "Perica";
}

void KapitalizirajPrviZnak(char* const tekst)
{
	if (tekst)
		tekst[0] = toupper(tekst[0]);
}

//void KapitalizirajPrviZnak(const char* const tekst)
//{
//	if (tekst)
//		tekst[0] = toupper(tekst[0]);
//}

string Kapitaliziraj(const string& tekst)
{
	string noviTekst(tekst);
	for (auto& znak : noviTekst)
		znak = toupper(znak);
	return noviTekst;
}

#include <initializer_list>        // definicija klase initializer_list

int Zbroji(initializer_list<int> pribrojnici)
{
	int rezultat = 0;
	for (int pribrojnik : pribrojnici)
		rezultat += pribrojnik;
	return rezultat;
}

double Nagib(double x, double y)
{
	return y / x;
}

char* Spoji(const char* prvi, const char* drugi)
{
	char spojeni[80];                // lokalni niz znakova
	char* indeks = spojeni;
	while (*prvi)
		*(indeks++) = *(prvi++);
	while (*drugi)
		*(indeks++) = *(drugi++);
	*indeks = '\0';
	return spojeni;            // oprez: vraćamo adresu lokalnog objekta
}


int main()
{
	char zloNeMisli[] = "mali Perica";
	KapitalizirajPrviZnak(zloNeMisli);
	char* nista = nullptr;
	ZamijeniTekst(nista);

	cout << Zbroji({ 1, 3, 5, 23, 14 }) << endl;

	float k = Nagib(3.2, -12.1);
	return 0;
}


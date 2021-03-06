#include <iostream>

constexpr long long Faktorijel(int n)
{
	long long rez = 1;
	for (int i = 2; i <= n; ++i)
		rez *= i;
	return rez;
}

//constexpr int Faktorijel(int n)
//{
//	return n > 1 ? n * Faktorijel(n - 1) : 1;
//}

// potenciranje:
constexpr double Potencija(double baza, int n)
{
	double rezultat = 1;
	while (--n >= 0)
		rezultat *= baza;
	return rezultat;
}
// zbroj razlomaka:
constexpr double BbpRazlomci(int i)
{
	return 4. / (8 * i + 1) - 2. / (8 * i + 4) -
			1. / (8 * i + 5) - 1. / (8 * i + 6);
}
// pojedini član reda:
constexpr double BbpClan(int i)
{
	return BbpRazlomci(i) / Potencija(16, i);
}
// rekurzivno zbrajamo članove reda:
constexpr double BbpSuma(int n)
{
	double suma = 0;
	for (int i = 0; i <= n; ++i)
		suma += BbpClan(i);
	return suma;
}
// dodajemo nove članove reda sve dok novi član reda postane zanemariv:
constexpr double Bbp(int i)
{
	if (BbpSuma(i) == BbpSuma(i + 1))
		return BbpSuma(i);
	return Bbp(i + 1);
}

// izračunava najveći argument za koji faktorijel neće izazvati preljev
constexpr int MaxBrojFjel()
{
	constexpr auto iMax = std::numeric_limits<long long>::max();
	long long fjel = 1;
	int n = 1;
	while (fjel < iMax / ++n)
		fjel *= n;
	return n - 1;
}

int main()
{
	constexpr int mf = MaxBrojFjel();
	std::cout << mf << std::endl;

	constexpr double mojPi = Bbp(0);
	std::cout << mojPi << std::endl;
	std::cout << mojPi - 3.1415926535897932384626433 << std::endl;

	double r;
	std::cin >> r;
	double povrsinaKruga = r * r * Bbp(0);

	int nula = 0;
	double pi = Bbp(nula);
	std::cout << pi << std::endl;

	constexpr auto a = Faktorijel(3);
	constexpr auto b = Faktorijel(5);
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	return 0;
}


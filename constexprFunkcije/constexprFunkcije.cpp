#include <iostream>

constexpr int Faktorijel(int n)
{
	if (n > 1)
		return n * Faktorijel(n - 1);
	return 1;
}

//constexpr int Faktorijel(int n)
//{
//	return n > 1 ? n * Faktorijel(n - 1) : 1;
//}

// rekurzivno potenciranje:
constexpr double Potencija(double baza, int n)
{
	double rezultat = 1;
	while (--n >= 0)
		rezultat *= baza;
	return rezultat;
	//return (i > 0) ? baza * Potencija(baza, i - 1) : 1;
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
constexpr double BbpSuma(int i)
{
	return (i >= 0) ? BbpSuma(i - 1) + BbpClan(i) : 0;
}
// dodajemo nove članove reda sve dok novi član reda postane zanemariv:
constexpr double Bbp(int i)
{
	if (BbpSuma(i) == BbpSuma(i + 1))
		return BbpSuma(i);
	return Bbp(i + 1);
	//return (BbpSuma(i) == BbpSuma(i + 1)) ? BbpSuma(i) : Bbp(i + 1);
}


// izračunava najveći argument za koji faktorijel neće izazvati preljev
constexpr int MaxBrojFjel(long long fjel, int n)
{
	return (fjel / n == 0) ? n - 1 : MaxBrojFjel(fjel / n, n + 1);
}
// konstantni izraz s kojim treba raditi usporedbu:
constexpr int iMax = MaxBrojFjel(std::numeric_limits<long long>::max(), 1);


int main()
{
	constexpr double mojPi = Bbp(0);
	std::cout << mojPi << std::endl;
	int nula = 0;
	double pi = Bbp(nula);
	std::cout << pi << std::endl;
	constexpr int a = Faktorijel(3);
	constexpr int b = Faktorijel(5);
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	return 0;
}


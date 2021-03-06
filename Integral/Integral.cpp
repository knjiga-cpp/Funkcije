#include <iostream>
#include <cmath>
using namespace std;

// deklaracije funkcija:
// deklaracije funkcija:
double Integral(double(*f)(double), double x0, double xn,
	double relGrijeh = 1.e-7, int circusMaximus = 1024);
double Podintegralna(double x);

int main()
{
	cout << Integral(sin, 0, 3.14159) << endl;
	cout << Integral(Podintegralna, 0, 3.) << endl;

	cout << Integral([](auto x) { return 2 * x * x - 3 * x + 2; }, 0, 2) << endl;

	auto parabola = [](auto x) { return x * x * x; };

	cout << Integral(parabola, 0, 3) << endl;

	cout << parabola(5) << endl;

	return 0;
}
// definicije funkcija
double Integral(double(*f)(double), double x0, double xn,
	double relGrijeh, int circusMaximus)
{
	long n = 1;                        // broj intervala
	const double h0 = xn - x0;         // širina intervala
	double staraSuma = 0.;
	double suma = (f(x0) + f(xn)) / 2;
	do
	{
		n *= 2;
		double doprinos = 0.;
		for (long i = 1; i < n; i += 2)
			doprinos += f(h0 * i / n + x0);
		staraSuma = suma;
		suma = staraSuma / 2 + doprinos / n;
	} while ((n <= circusMaximus) && (suma != 0) &&
		(fabs(1. - staraSuma / suma) > relGrijeh));
	return suma * h0;
}

double Podintegralna(double x)
{
	return x * x;
}

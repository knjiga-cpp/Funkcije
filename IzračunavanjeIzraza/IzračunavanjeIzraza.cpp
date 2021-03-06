#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class VrstaUnosa {
	Broj, Operator,
	LijevaZagrada, DesnaZagrada,
	Funkcija
};

enum class Operator { Zbroji, Oduzmi, Pomnozi, Podijeli };

struct Unos
{
	VrstaUnosa vrsta;
	// anonimna unija:
	union
	{
		double broj;
		Operator operacija;
		const char* funkcija;
	};
};

#include <map>
// ovo treba umetnuti ispred gornjeg kôda:
map<Operator, int> hijerarhija
{
	// zadajemo parove ključ-vrijednost:
	{ Operator::Zbroji, 1 },
	{ Operator::Oduzmi, 1 },
	{ Operator::Pomnozi, 2 },
	{ Operator::Podijeli, 2 }
};

// deklaracije funkcija koje funkcija main koristi:
void UnosLijevihZagrada(const string& izraz, size_t& pozicija,
	vector<Unos>& unosi,
	int& brojOtvorenihZagrada);
bool UnosDesnihZagrada(const string& izraz, size_t& pozicija,
	vector<Unos>& unosi, int& brojOtvorenihZagrada);
void UnosBroja(const string& izraz, size_t& pozicija,
	vector<Unos>& unosi);
void UnosOperatora(const string& izraz, size_t& pozicija,
	vector<Unos>& unosi);
void IzracunajOperaciju(vector<Operator>& operatori,
	vector<double>& operandi);
double IzracunajIzraz(const vector<Unos>& unosi);

int main()
{
	string izraz;
	getline(cin, izraz);
	try
	{
		vector<Unos> unosi;
		size_t pozicija = 0;
		int brojOtvorenihZagrada = 0;
		// preskočimo početne praznine:
		pozicija = izraz.find_first_not_of(' ', pozicija);
		// postupak učitavanja niza broj-operator-broj-operator-...
		// ponavlja se sve dok ima znakova u izrazu:
		while (pozicija != string::npos)
		{
			// prvo učitavamo eventualne lijeve zagrade:
			UnosLijevihZagrada(izraz, pozicija, unosi,
				brojOtvorenihZagrada);
			// učitavamo prvi broj:
			UnosBroja(izraz, pozicija, unosi);
			// ako nismo došli do kraja izraza ili desne zagrade,
			// tada slijede operator i desni broj:
			while ((pozicija != string::npos)
				&& (izraz.at(pozicija) != ')'))
			{
				UnosOperatora(izraz, pozicija, unosi);
				// učitavamo eventualne lijeve zagrade:
				UnosLijevihZagrada(izraz, pozicija, unosi,
					brojOtvorenihZagrada);
				UnosBroja(izraz, pozicija, unosi);
			}
			// učitavamo desne zagrade; nakon zadnje zagrade 
			// može slijediti operator, osim ako je izraz gotov:
			if (UnosDesnihZagrada(izraz, pozicija, unosi,
				brojOtvorenihZagrada)
				&& (pozicija != string::npos))
			{
				UnosOperatora(izraz, pozicija, unosi);
			}
		}
		if (brojOtvorenihZagrada > 0)
			throw runtime_error("Višak lijevih zagrada");

		// postupak izračunavanja:
		cout << IzracunajIzraz(unosi) << endl;
	}
	catch (invalid_argument)
	{
		cerr << "Neispravni operand" << endl;
	}
	catch (runtime_error iznimka)
	{
		cerr << iznimka.what() << endl;
	}

	return 0;
}

void UnosLijevihZagrada(const string& izraz, size_t& pozicija,
	vector<Unos>& unosi, int& brojOtvorenihZagrada)
{
	// može biti više lijevih zagrada za redom:
	while (izraz.at(pozicija) == '(')
	{
		Unos unosLijeveZagrade;
		unosLijeveZagrade.vrsta = VrstaUnosa::LijevaZagrada;
		unosi.push_back(unosLijeveZagrade);
		++brojOtvorenihZagrada;
		pozicija = izraz.find_first_not_of(' ', ++pozicija);
	}
}

bool UnosDesnihZagrada(const string& izraz, size_t& pozicija,
	vector<Unos>& unosi, int& brojOtvorenihZagrada)
{
	// nema desne zagrade:
	if (pozicija == string::npos || izraz.at(pozicija) != ')')
		return false;
	// može biti više desnih zagrada za redom:
	while (pozicija != string::npos && izraz.at(pozicija) == ')')
	{
		Unos unosDesneZagrade;
		unosDesneZagrade.vrsta = VrstaUnosa::DesnaZagrada;
		unosi.push_back(unosDesneZagrade);
		--brojOtvorenihZagrada;
		if (brojOtvorenihZagrada < 0)
		{
			string poruka("Desna zagrada viška na poziciji ");
			poruka.append(to_string(pozicija));
			throw runtime_error(poruka);
		}
		pozicija = izraz.find_first_not_of(' ', ++pozicija);
	}
	return true;
}

void UnosBroja(const string& izraz, size_t& pozicija,
	vector<Unos>& unosi)
{
	size_t brojZnakova;
	double broj = stod(&izraz[pozicija], &brojZnakova);
	Unos unosBroja;
	unosBroja.vrsta = VrstaUnosa::Broj;
	unosBroja.broj = broj;
	unosi.push_back(unosBroja);
	pozicija = izraz.find_first_not_of(' ', pozicija + brojZnakova);
}

void UnosOperatora(const string& izraz, size_t& pozicija,
	vector<Unos>& unosi)
{
	char operacija = izraz.at(pozicija);
	Unos unosOperatora;
	unosOperatora.vrsta = VrstaUnosa::Operator;
	switch (operacija)
	{
	case '+':
		unosOperatora.operacija = Operator::Zbroji;
		break;
	case '-':
		unosOperatora.operacija = Operator::Oduzmi;
		break;
	case '*':
		unosOperatora.operacija = Operator::Pomnozi;
		break;
	case '/':
		unosOperatora.operacija = Operator::Podijeli;
		break;
	default:
		throw runtime_error{ "Neispravni operator" };
	}
	unosi.push_back(unosOperatora);
	pozicija = izraz.find_first_not_of(' ', ++pozicija);
}

void IzracunajOperaciju(vector<Operator>& operatori,
	vector<double>& operandi)
{
	Operator prethodniOperator = operatori.back();
	operatori.pop_back();
	double desni = operandi.back();
	operandi.pop_back();
	double lijevi = operandi.back();
	operandi.pop_back();
	switch (prethodniOperator)
	{
	case Operator::Zbroji:
		operandi.push_back(lijevi + desni);
		break;
	case Operator::Oduzmi:
		operandi.push_back(lijevi - desni);
		break;
	case Operator::Pomnozi:
		operandi.push_back(lijevi * desni);
		break;
	case Operator::Podijeli:
		operandi.push_back(lijevi / desni);
		break;
	}
}

double IzracunajIzraz(const vector<Unos>& unosi)
{
	vector<Operator> operatori;
	vector<double> operandi;
	for (vector<Unos>::const_iterator it = unosi.begin();
		it != unosi.end(); ++it)
	{
		Unos unos = *it;
		if (unos.vrsta == VrstaUnosa::LijevaZagrada)
		{
			vector<Unos>::const_iterator pocetakZagrade = it;
			int otvoreneZagrade = 1;
			// nađi pripadajuću desnu zagradu:
			while (otvoreneZagrade > 0)
			{
				++it;
				if (it->vrsta == VrstaUnosa::LijevaZagrada)
					++otvoreneZagrade;
				if (it->vrsta == VrstaUnosa::DesnaZagrada)
					--otvoreneZagrade;
			}
			// izluči izraz imeđu lijeve i desne zagrade:
			vector<Unos> unutarZagrade(pocetakZagrade + 1, it);
			// izračunaj izraz između lijeve i desne zagrade:
			double rezultatZagrade = IzracunajIzraz(unutarZagrade);
			operandi.push_back(rezultatZagrade);
		}
		else if (unos.vrsta == VrstaUnosa::Broj)
			operandi.push_back(unos.broj);
		else if (unos.vrsta == VrstaUnosa::Operator)
		{
			Operator zadnjiOperator = unos.operacija;
			while (!operatori.empty()
				&& (hijerarhija[operatori.back()]
					>= hijerarhija[zadnjiOperator]))
			{
				IzracunajOperaciju(operatori, operandi);
			}
			operatori.push_back(zadnjiOperator);
		}
	}
	while (!operatori.empty())
		IzracunajOperaciju(operatori, operandi);
	// konačni rezultat izraza:
	return operandi[0];
}

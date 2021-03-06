#include <iostream>

using namespace std;

enum class Tip
{
	CijeliBroj, DecimalniBroj, ZnakovniNiz
};

void Ispisi(void* podatak, Tip tipPodatka)
{
	switch (tipPodatka)
	{
	case Tip::CijeliBroj:
		// pokazivač pretvaramo u int* i dereferenciramo:
		cout << *static_cast<int*>(podatak) << endl;
		break;
	case Tip::DecimalniBroj:
		// pokazivač pretvaramo u double* i dereferenciramo:
		cout << *static_cast<double*>(podatak) << endl;
		break;
	case Tip::ZnakovniNiz:
		// pokazivač pretvaramo u char*, ali NE dereferenciramo:
		cout << static_cast<char*>(podatak) << endl;
		break;
	}
}

int main()
{
    std::cout << "Hello World!\n"; 
}

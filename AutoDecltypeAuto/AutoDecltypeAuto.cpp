#include <iostream>
using namespace std;

auto DuljiA(string prvi, string drugi)
{
	return prvi.size() > drugi.size() ? prvi : drugi;
}

auto& DuljiARef(string& prvi, string& drugi)
{
	return prvi.size() > drugi.size() ? prvi : drugi;
}

decltype(auto) DuljiDa(string& prvi, string& drugi)
{
	return prvi.size() > drugi.size() ? prvi : drugi;
}

template <typename Tip>
Tip& VeciRef(Tip& a, Tip& b)
{
	return a > b ? a : b;
}

template <typename Tip>
decltype(auto) VeciRefDa(Tip& a, Tip& b)
{
    return a > b ? a : b;
}

template <typename Tip>
auto VeciRefA(Tip& a, Tip& b)
{
    return a > b ? a : b;
}

template <typename Tip>
auto& VeciRefAr(Tip& a, Tip& b)
{
    return a > b ? a : b;
}

int main()
{
	//string patuljak{ "kratak" };
	//string dugi{ "dugačak" };

	//auto duljiA = DuljiA(patuljak, dugi);
	//auto duljiARef = DuljiARef(patuljak, dugi);
	//auto& duljiDa = DuljiDa(patuljak, dugi);
	//duljiA += "  još dulji";
	//duljiARef += "  još dulji";
	//duljiDa += "  još dulji";


    int a = 3;
    int b = 5;
	++VeciRef(a, b);
	auto& ref = VeciRef(a, b);
	auto& refDa = VeciRefDa(a, b);
    auto refA = VeciRefA(a, b);
    auto& refAr = VeciRefAr(a, b);

	++ref;
    ++refDa;
    ++refA;
    ++refAr;

    // samo za decltype(auto)
    //VeciRef(a, b)++;

    return 0;
}

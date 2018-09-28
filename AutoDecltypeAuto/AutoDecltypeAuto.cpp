#include <iostream>
using namespace std;

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
    int a = 3;
    int b = 5;
    auto& refDa = VeciRefDa(a, b);
    auto refA = VeciRefA(a, b);
    auto& refAr = VeciRefAr(a, b);

    ++refDa;
    ++refA;
    ++refAr;

    // samo za decltype(auto)
    //VeciRef(a, b)++;

    return 0;
}

#include <iostream>
using namespace std;

//template <typename Tip1, typename Tip2>
//auto Veci(const Tip1& a, const Tip2& b)
//{
//	return a > b ? a : b;
//}

template <typename Tip1, typename Tip2>
decltype(auto) Veci(const Tip1& a, const Tip2& b)
{
	return a > b ? a : b;
}

int main()
{
	auto a = Veci(3, 4.25);							// želimo da vrati 4.25
	auto b = Veci(4.25, 5);							// želimo da vrati 5

	Veci(3, 5);							// želimo da vrati 5
	Veci(string{ "abeceda" }, string{ "alfabet" });		  // vrati "alfabet"

	return 0;
}

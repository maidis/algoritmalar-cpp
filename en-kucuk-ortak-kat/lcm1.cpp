#include <iostream>
#include <numeric>
#include <vector>

int gcd1(int const a, int const b)
{
   return b == 0 ? a : gcd1(b, a % b);
}

int lcm1(int const a, int const b)
{
   int h = gcd1(a, b);
   return h ? (a * (b / h)) : 0;
}

int lcm2(int const a, int const b)
{
   return std::lcm(a, b);
}

int main()
{
    std::cout << "Sayıları giriniz: ";

    unsigned int a, b;
    std::cin >> a >> b;

    std::cout << "lcm(" << a << ", " << b << ") = "
              << lcm1(a, b) << std::endl;

    std::cout << "std lcm(" << a << ", " << b << ") = "
              << lcm2(a, b) << std::endl;
}

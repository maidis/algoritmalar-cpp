#include <iostream>
#include <numeric>

unsigned int gcd1(unsigned int const a, unsigned int const b)
{
   return b == 0 ? a : gcd1(b, a % b);
}

unsigned int gcd2(unsigned int a, unsigned int b)
{
   while (b != 0)
   {
      unsigned int r = a % b;
      a = b;
      b = r;
   }

   return a;
}

int main()
{
   std::cout << "Sayıları giriniz: ";

   unsigned int a, b;
   std::cin >> a >> b;

   std::cout << "ozy gcd(" << a << ", " << b << ") = "
             << gcd1(a, b) << std::endl;

   std::cout << "ite gcd(" << a << ", " << b << ") = "
             << gcd2(a, b) << std::endl;

   std::cout << "std gcd(" << a << ", " << b << ") = "
             << std::gcd(a, b) << std::endl;
}

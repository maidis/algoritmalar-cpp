#include <iostream>
#include <utility>

template<typename T1, typename T2>
T1 gcd(T1 a, T2 b)
{
    // a >= b, a * b != 0
    if(a < b)
    {
        std::swap(a, b);
    }

    T1 r;
    while(r = a % b)
    {
        a = b;
        b = r;
    }

    return b;
}

template<typename T1, typename T2, typename... Types>
T1 gcd(T1 a, T2 b, Types... args)
{
   return gcd(a, gcd(b, args...));
}

int main()
{
    std::cout << "gcd(10, 20, 30, 40, 55) = "
              << gcd(10, 20, 30, 40, 55) << std::endl;
}

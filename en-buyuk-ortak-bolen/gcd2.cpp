#include <iostream>

int gcd(unsigned int u, unsigned int v)
{
    // temel durumlar (sonlandırmalar)
    if (u == v)
    {
        return u;
    }

    if (u == 0)
    {
        return v;
    }
    if (v == 0)
    {
        return u;
    }
    // GCD(0, 0) = 0

    // 2'nin katlarını ara
    if (~u & 1) // u çift
    {
        if (v & 1) // v tek
        {
            return gcd(u >> 1, v);
        }
        else // hem u hem de v çift
        {
            return gcd(u >> 1, v >> 1) << 1;
        }
    }

    if (~v & 1) // u tek, v çift
    {
        return gcd(u, v >> 1);
    }

    // büyük sayıyı küçült
    if (u > v)
    {
        return gcd((u - v) >> 1, v);
    }

    return gcd((v - u) >> 1, u);
}

int main()
{
    std::cout << "Sayıları giriniz: ";

    unsigned int u, v;
    std::cin >> u >> v;

    std::cout << "gcd(" << u << ", " << v << ") = "
              << gcd(u, v) << std::endl;

    return 0;
}

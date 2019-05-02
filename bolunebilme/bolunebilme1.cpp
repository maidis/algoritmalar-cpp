#include <iostream>

int main()
{
    unsigned int limit = 0;

    std::cout << "Üst sınır: ";
    std::cin >> limit;

    unsigned long long sum = 0;
    bool isDivisible = 0;

    for (unsigned int i = 3; i < limit; ++i)
    {
        if (i % 3 == 0)
        {
            isDivisible = 1;
        }
        else if (i % 5 == 0)
        {
            isDivisible = 1;
        }

        if (isDivisible)
        {
            sum += i;
        }

        isDivisible = 0;
    }

    // 11 için: 3 + 5 + 6 + 9 + 10 = 33
    std::cout << "Toplam: " << sum << std::endl;
}

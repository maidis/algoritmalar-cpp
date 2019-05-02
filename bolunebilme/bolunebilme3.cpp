#include <iostream>

int main()
{
    unsigned int limit = 0;

    std::cout << "Üst sınır: ";
    std::cin >> limit;

    unsigned int limit3 = (limit - 1) / 3;
    unsigned int limit5 = (limit- 1) / 5;
    unsigned int limit15 = (limit - 1) / 15;

    unsigned long long sum = 0;

    sum = 0.5 * 3 * limit3 * (limit3 + 1) + 0.5 * 5 * limit5 * (limit5 + 1) - 0.5 * 15 * limit15 * (limit15 + 1);

    std::cout << "Toplam: " << sum << std::endl;
}

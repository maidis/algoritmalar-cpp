#include <iostream>
#include <numeric>
#include <vector>

template<class InputIt>
int lcmr(InputIt first, InputIt last)
{
    return std::accumulate(first, last, 1, std::lcm<int, int>);
}

int main()
{
    int n = 0;
    std::cout << "Girdi sayısı: ";
    std::cin >> n;

    std::vector<int> numbers;
    std::cout << "Sayıları giriniz: ";

    for (unsigned int i = 0; i < n; ++i)
    {
       int v{ 0 };
       std::cin >> v;
       numbers.push_back(v);
    }

    std::cout << "lcm = " << lcmr(std::begin(numbers), std::end(numbers)) << '\n';
}

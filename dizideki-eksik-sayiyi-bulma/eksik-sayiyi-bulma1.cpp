#include <iostream>
#include <array>

template<std::size_t SIZE>
unsigned long long findMissing(std::array<int, SIZE>& arr)
{
    unsigned long long total;
    total = (SIZE) * (SIZE + 1) / 2;
    for(auto& e : arr)
    {
        total -= e;
    }
    return total;
}

int main()
{
    std::array<int, 10> a1{ {10, 2, 5, 6, 3, 7, 8, 4, 9} };
    int miss = findMissing(a1);
    std::cout << miss;
    return 0;
}

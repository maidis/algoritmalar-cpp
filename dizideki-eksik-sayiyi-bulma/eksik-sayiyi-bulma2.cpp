#include <iostream>
#include <array>

template<std::size_t SIZE>
int findMissing(std::array<int, SIZE>& arr)
{
    int x1 = arr[0];
    int x2 = 1;

    for (int i = 1; i < SIZE; ++i)
    {
        x1 ^= arr[i];
    }

    for (int i = 2; i <= SIZE; ++i)
    {
        x2 ^= i;
    }

    return (x1 ^ x2);
}

int main()
{
    std::array<int, 10> a1{ {1, 2, 5, 6, 3, 9, 8, 4, 10} };

    std::cout << findMissing(a1) << std::endl;

    return 0;
}

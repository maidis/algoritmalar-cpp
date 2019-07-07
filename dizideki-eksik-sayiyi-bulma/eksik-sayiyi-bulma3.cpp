#include <iostream>
#include <algorithm>
#include <array>

template<std::size_t SIZE>
int findMissing(std::array<int, SIZE>& arr)
{
    std::sort(arr.begin(), arr.end());

    if (arr.at(1) != 1) // arr.front() has 0
    {
        return 1;
    }
    else if (arr.back() != SIZE)
    {
        return SIZE;
    }
    else
    {
        for (int i = 0; i < SIZE; ++i)
        {
            if (arr.at(i + 1) - arr.at(i) != 1)
            {
                return arr.at(i) + 1;
            }
        }
    }
}

int main()
{
    std::array<int, 10> a1{ {3, 10, 5, 6, 7, 1, 8, 4, 2} };

    std::cout << findMissing(a1) << std::endl;

    return 0;
}

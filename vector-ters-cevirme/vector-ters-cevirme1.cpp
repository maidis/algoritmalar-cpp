#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> &v)
{
    for (T const& i: v)
    {
        os << i << " ";
    }

    return os;
}

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::cout << "Orijinal vector: " << v << '\n';

    std::reverse(v.begin(), v.end());
    std::cout << "Çevrilmiş vector: " << v << '\n';

    return 0;
}

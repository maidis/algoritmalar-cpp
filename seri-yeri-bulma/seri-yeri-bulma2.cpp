#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

int main()
{
    std::vector<int> v = {1, 1, 1, 0, 0, 1, 1, 0, 1, 1}; // {(0, 2), (5, 6), (8, 9)}

    int q = 1;

    auto i = std::find(v.begin(), v.end(), q);
    std::vector<std::size_t> result;
    while(i != v.end())
    {
        auto pv = std::prev(i, 1);
        auto nt = std::next(i, 1);

        if (*pv != q)
            result.push_back(std::distance(v.begin(), i));
        if (*nt != q)
            result.push_back(std::distance(v.begin(), i));
        i = std::find(i + 1, v.end(), q);
    }

    std::vector <std::pair<int, int>> vect;

    for (int i = 0; i < result.size(); i = i + 2)
    {
        vect.push_back(std::make_pair(result[i], result[i+1]));
    }

    std::cout << '{';
    for (auto i = vect.begin(); i != vect.end(); ++i)
    {
        std::cout << '(' << std::get<0>(*i) << ", " << std::get<1>(*i);

        if (std::next(i) != vect.end())
        {
            std::cout << "), ";
        }
        else
        {
            std::cout << ")";
        }
    }
    std::cout << '}' << std::endl;
}

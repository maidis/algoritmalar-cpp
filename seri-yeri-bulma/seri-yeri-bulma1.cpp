#include <iostream>
#include <vector>
#include <utility>

int main()
{
    std::vector<int> v = {1, 1, 1, 0, 0, 1, 1, 0, 1, 1}; // {(0, 2), (5, 6), (8, 9)}
    int a, b;
    int q = 1;
    std::vector <std::pair<int, int>> vect;
    bool inSeries = false;

    for (int i = 0; i < v.size(); ++i)
    {
        if (v[i] != q && inSeries == false)
        {
            continue;
        }
        else if (v[i] == q && inSeries == false)
        {
            inSeries = true;
            a = i;
            b = i;
            if (i == v.size() - 1)
            {
                vect.push_back(std::make_pair(a, b));
            }
        }
        else if ( v[i] == q && inSeries == true)
        {
            b = i;
            if (i == v.size() - 1)
            {
                vect.push_back(std::make_pair(a, b));
            }
        }
        else if (v[i] != q && inSeries == true)
        {
            vect.push_back(std::make_pair(a, b));
            inSeries = false;
        }
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

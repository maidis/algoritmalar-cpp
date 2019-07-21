#include <iostream>
#include <algorithm>
#include <set>

int main()
{
    int p = 1000;

    std::set <std::pair<int, int>> ucgen;

    if (p % 2 != 0)
    {
        return 0;
    }
    else
    {
        for (float b = 1; b < p/2; b++)
        {
            float a = (p/2) * ((p - 2*b) / (p - b));
            int inta = (int) a;
            int c = p - a - b;
            if (a == inta)
            {
                if (a < b)
                {
                    ucgen.insert(std::make_pair(a, b));
                }
                else
                {
                    ucgen.insert(std::make_pair(b, a));
                }
            }
        }
    }

    for (auto i : ucgen)
    {
        std::cout << std::get<0>(i) << ", " << std::get<1>(i)
                  << ", " << p - std::get<0>(i) - std::get<1>(i) << std::endl;
    }

    return 0;
}

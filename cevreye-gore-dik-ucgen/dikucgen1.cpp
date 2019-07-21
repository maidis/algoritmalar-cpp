#include <iostream>

int main()
{
    int p = 3000;
    for (int i = 1; i < p/2; i++)
    {
        for (int j = i+1; j < p/2; j++)
        {
            int c = p - i - j;
            if (i*i + j*j == c*c)
            {
                std::cout << i << ", " << j << ", " << c << std::endl;
            }
        }
    }

    return 0;
}

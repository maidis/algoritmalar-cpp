#include <bits/stdc++.h>
#include <bitset>
#include <iostream>

int swapNibbles(int x)
{
    return ( (x & 0x0F) << 4 | (x & 0xF0) >> 4 );
}


int main()
{
    int x = 100;
    std::cout << x << " - " << std::bitset<8>(x) << '\n';
    int y = swapNibbles(x);
    std::cout << y << " - " << std::bitset<8>(y) << '\n';
    return 0;
}

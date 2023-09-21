#include <iostream>

int main()
{
    unsigned char x = 255;
    unsigned char mask = 1;
    x = x & (~(mask << 4));
    std::cout << (int)x;
    return 0;
}
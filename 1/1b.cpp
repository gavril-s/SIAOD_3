#include <iostream>

int main()
{
    unsigned char x = 0;
    unsigned char mask = 1;
    x = x | (mask << 6);
    std::cout << (int)x;
    return 0;
}
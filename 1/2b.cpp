#include <iostream>
//#include <bitset>

typedef unsigned long long ull;

int main()
{
    const size_t size = 64;
    ull bit_array = 0;

    for (int i = 0; i < size; i++)
    {
        ull buff = 0;
        std::cin >> buff;

        ull mask = 1;
        bit_array = bit_array | (mask << buff);
    }

    //std::cout << std::bitset<size> (bit_array);

    ull mask = 1;
    for (int i = 0; i < size; i++)
    {
        if (bit_array & (mask << i))
        {
            std::cout << i << ' ';
        }
    }
    std::cout << std::endl;

    return 0;
}
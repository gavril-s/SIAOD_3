#include <iostream>
//#include <bitset>

typedef unsigned char byte;

int main()
{
    const size_t size = 8;
    byte bit_array = 0;

    for (int i = 0; i < size; i++)
    {
        int buff = 0;
        std::cin >> buff;

        byte mask = 1;
        bit_array = bit_array | (mask << buff);
    }

    //std::cout << std::bitset<size> (bit_array);

    byte mask = 1;
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
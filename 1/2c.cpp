#include <iostream>

typedef unsigned long long ull;
typedef unsigned char byte;

int main()
{
    const size_t size = 64;
    const size_t byte_size = sizeof(byte) * 8;
    const size_t byte_array_size = size / byte_size;
    byte* byte_array = new byte[byte_array_size];
    for (int i = 0; i < byte_array_size; i++)
    {
        byte_array[i] = 0;
    }

    for (int i = 0; i < size; i++)
    {
        ull buff = 0;
        std::cin >> buff;

        size_t index = buff / byte_size;
        byte shift = buff % byte_size;
        byte mask = 1;
        byte_array[index] = byte_array[index] | (mask << shift);
    }

    byte mask = 1;
    for (int i = 0; i < byte_array_size; i++)
    {
        for (int j = 0; j < byte_size; j++)
        {
            if (byte_array[i] & (mask << j))
            {
                std::cout << i * byte_size + j << ' ';
            }
        }
    }
    std::cout << std::endl;

    delete[] byte_array;
    return 0;
}
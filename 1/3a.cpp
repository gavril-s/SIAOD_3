#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

typedef unsigned long long ull;
typedef unsigned char byte;

int main()
{
    const size_t size = 8388608; // 1 Mb in bits
    const size_t byte_size = sizeof(byte) * 8;
    const size_t byte_array_size = size / byte_size;
    byte* byte_array = new byte[byte_array_size];
    for (int i = 0; i < byte_array_size; i++)
    {
        byte_array[i] = 0;
    }

    std::cout << "Enter filename: ";
    std::string filename;
    std::cin >> filename;
    std::ifstream input_stream(filename);

    auto start = std::chrono::high_resolution_clock::now();

    ull buff = 0;
    while (input_stream >> buff)
    {
        size_t index = buff / byte_size;
        byte shift = buff % byte_size;
        byte mask = 1;
        byte_array[index] = byte_array[index] | (mask << shift);
    }

    std::ofstream output_stream("out.txt");
    byte mask = 1;
    for (int i = 0; i < byte_array_size; i++)
    {
        for (int j = 0; j < byte_size; j++)
        {
            if (byte_array[i] & (mask << j))
            {
                output_stream << i * byte_size + j << ' ';
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Reading, sorting and writing took " << duration.count() / 1000.0 << " seconds\n";

    delete[] byte_array;
    return 0;
}
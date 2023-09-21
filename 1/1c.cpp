#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <bitset>

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    unsigned int x = 25;
    const int n = sizeof(int) * 8;
    unsigned maska = (1 << n - 1);
    cout << "Initial mask: " << bitset<n> (maska) << endl;
    cout << "Result: ";

    for (int i = 1; i <= n; i++)
    {
        cout << ((x & maska) >> (n - i));
        maska = maska >> 1;
    }
    cout << endl;

    system("pause");
    return 0;
}
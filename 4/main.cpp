#include <iostream>
#include "bin_tree.h"

int main()
{
    bin_tree<double> t;
    t.insert(5);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(1);
    t.insert(0);
    t.insert(6);
    t.insert(7);
    t.insert(5.0);
    t.insert(1.1);
    t.insert(2.5);

    t.print();

    return 0;
}
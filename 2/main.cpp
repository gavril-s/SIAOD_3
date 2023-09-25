#include <iostream>
#include <string>
#include "book_hashmap.h"

int main()
{
    book_hashmap* books = new book_hashmap();
    book b1(123456789013, "ME", "SAMPLE TEXT");
    book b2(123456789012, "ME", "SAMPLE TEXT");
    book b3(123456789012, "ME", "SAMPLE TEXT");
    book b4(123456789013, "ME", "SAMPLE TEXT");
    books->insert(b1);
    books->insert(b2);
    books->insert(b3);
    books->insert(b4);
    std::cout << "INSERTED\n";
    std::cout << (*books) << "\n\n";
    std::cout << books->search(123456789012) << std::endl;
    //std::cout << books->search(123456789013) << std::endl;
    std::cout << books->remove_by_isbn(123456789012) << std::endl;
    std::cout << books->search(123456789012) << "\n\n";
    std::cout << (*books) << std::endl;
    return 0;
}
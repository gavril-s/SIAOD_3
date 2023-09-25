#ifndef BOOK_HASHMAP_H
#define BOOK_HASHMAP_H

#include <iostream>
#include <string>

#define HASHMAP_SIZE 1000000 // ~ 35 Mb
typedef unsigned long long ull;

class book // 32 bytes
{
private:
    ull isbn;
    std::string author;
    std::string name;
public:
    book();
    book(ull isbn, std::string author, std::string name);
    book(const book& b);
    ull get_isbn() const;
    std::string get_author() const;
    std::string get_name() const;
    friend std::ostream& operator<<(std::ostream& os, const book& b);
};

class book_hashmap
{
private:
    book* books[HASHMAP_SIZE];
    size_t hash(ull isbn) const;
    size_t hash(const book& b) const;
public:
    book_hashmap();
    int insert(const book& b);
    bool remove_by_isbn(ull isbn);
    bool remove_by_index(size_t index);
    int search(ull isbn) const;
    friend std::ostream& operator<<(std::ostream& os, const book_hashmap& bh);
};

#endif
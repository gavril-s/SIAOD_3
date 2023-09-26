#ifndef BOOK_HASHMAP_H
#define BOOK_HASHMAP_H

#include <iostream>
#include <string>

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
    friend std::istream& operator>>(std::istream& is, book& b);
};

class book_hashmap
{
private:
    const size_t initial_size = 1000;
    const float capacity = 1.5f;
    size_t size;
    book** books;
    size_t hash(ull isbn) const;
    size_t hash(const book& b) const;
    void resize();
public:
    book_hashmap();
    size_t hashmap_size() const;
    book* get(size_t index) const;
    int search(ull isbn) const;
    size_t insert(const book& b);
    bool remove_by_isbn(ull isbn);
    bool remove_by_index(size_t index);
    friend std::ostream& operator<<(std::ostream& os, const book_hashmap& bh);
};

#endif
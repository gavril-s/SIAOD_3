#include "book_hashmap.h"

book::book() : isbn{0} {}

book::book(ull isbn, std::string author, std::string name) 
{
    this->isbn = isbn;
    this->author = author;
    this->name = name;
}

book::book(const book& b)
{
    this->isbn = b.get_isbn();
    this->author = b.get_author();
    this->name = b.get_name();
}

ull book::get_isbn() const
{
    return isbn;
}

std::string book::get_author() const
{
    return author;
}

std::string book::get_name() const
{
    return name;
}

std::ostream& operator<<(std::ostream& os, const book& b)
{
    os << b.isbn << ": " << b.author << " - " << b.name;
    return os;
}

size_t book_hashmap::hash(ull isbn) const
{
    return isbn % HASHMAP_SIZE;
}

size_t book_hashmap::hash(const book& b) const
{
    return hash(b.get_isbn());
}

book_hashmap::book_hashmap()
{
    for (int i = 0; i < HASHMAP_SIZE; ++i)
    {
        books[i] = nullptr;
    }
}

size_t book_hashmap::insert(const book& b)
{
    size_t index = hash(b);
    while (books[index] != nullptr)
    {
        ++index;
        if (index >= HASHMAP_SIZE)
        {
            return -1;
        }
    }

    books[index] = new book(b);
    return index;
}

bool book_hashmap::remove_by_isbn(ull isbn)
{
    size_t index = search(isbn);
    if (index == -1)
    {
        return false;
    }
    else
    {
        return remove_by_index(index);
    }
}

bool book_hashmap::remove_by_index(size_t index)
{
    if (index >= HASHMAP_SIZE || books[index] == nullptr)
    {
        return false;
    }

    books[index] = nullptr;
    return true;
}

size_t book_hashmap::search(ull isbn) const
{
    size_t index = hash(isbn);
    for (; index < HASHMAP_SIZE; ++index)
    {
        if (books[index] != nullptr && books[index]->get_isbn() == isbn)
        {
            return index;
        }
    }

    return -1;
}

std::ostream& operator<<(std::ostream& os, const book_hashmap& bh)
{
    for (int i = 0; i < HASHMAP_SIZE; i++)
    {
        if (bh.books[i] != nullptr)
        {
            os << i << " --> " << (*bh.books[i]) << '\n';
        }
    }

    return os;
}
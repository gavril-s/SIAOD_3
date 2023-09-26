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

std::istream& operator>>(std::istream& is, book& b)
{
    is >> b.isbn >> b.author >> b.name;
    return is;
}

size_t book_hashmap::hash(ull isbn) const
{
    return isbn % size;
}

size_t book_hashmap::hash(const book& b) const
{
    return hash(b.get_isbn());
}

void book_hashmap::resize()
{
    size_t old_size = size;
    book** old_books = new book*[old_size];
    for (size_t i = 0; i < old_size; ++i)
    {
        if (books[i] != nullptr)
        {
            old_books[i] = new book(*books[i]);
        }
        else
        {
            old_books[i] = nullptr;
        }
    }

    delete[] books;
    size = (size_t)(size * capacity);
    books = new book*[size];
    for (size_t i = 0; i < size; ++i)
    {
        books[i] = nullptr;
    }

    for (size_t i = 0; i < old_size; ++i)
    {
        if (old_books[i] != nullptr)
        {
            insert(*old_books[i]);
        }
    }
    delete[] old_books;
}

book_hashmap::book_hashmap()
{
    size = initial_size;
    books = new book*[size];
    for (size_t i = 0; i < size; ++i)
    {
        books[i] = nullptr;
    }
}

size_t book_hashmap::hashmap_size() const
{
    return size;
}

book* book_hashmap::get(size_t index) const
{
    if (index >= size)
    {
        return nullptr;
    }

    return books[index];
}

int book_hashmap::search(ull isbn) const
{
    size_t index = hash(isbn);
    for (; index < size; ++index)
    {
        if (books[index] != nullptr && books[index]->get_isbn() == isbn)
        {
            return index;
        }
    }

    return -1;
}

size_t book_hashmap::insert(const book& b)
{
    size_t index = hash(b);
    while (books[index] != nullptr)
    {
        ++index;
        if (index >= size)
        {
            resize();
            return insert(b);
        }
    }

    books[index] = new book(b);
    return index;
}

bool book_hashmap::remove_by_isbn(ull isbn)
{
    int index = search(isbn);
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
    if (index >= size || books[index] == nullptr)
    {
        return false;
    }

    books[index] = nullptr;
    return true;
}

std::ostream& operator<<(std::ostream& os, const book_hashmap& bh)
{
    for (size_t i = 0; i < bh.size; ++i)
    {
        if (bh.books[i] != nullptr)
        {
            os << i << " --> " << (*bh.books[i]) << '\n';
        }
    }

    return os;
}
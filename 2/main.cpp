#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "book_hashmap.h"

typedef unsigned long long ull;

void fill_hashmap_sample_data(book_hashmap* books)
{
    std::vector<std::tuple<ull, std::string, std::string>> data = {
        std::make_tuple(978723638028, "Tolstoi", "Anna Karenina"),
        std::make_tuple(978960292031, "Dostoevsky", "Crime and Punishment"),
        std::make_tuple(978228419636, "Pelevin", "Chapayev and Void"),
        std::make_tuple(978519673587, "Yerofeyev", "Moscow-Petushki"),
        std::make_tuple(978968135006, "Bulgakov", "The Master and Margarita"),
        std::make_tuple(978581156609, "Gogol", "Dead Souls")
    };

    for (auto entry : data)
    {
        book b = book(std::get<0>(entry), std::get<1>(entry), std::get<2>(entry));
        books->insert(b);
    }
}

void run_shell()
{
    book_hashmap* books = new book_hashmap();
    
    std::cout << "========================================\n"
              << "1 - Заполнить таблицу тестовыми записями\n"
              << "2 - Продолжить без заполнения\n";
    int fill_hashmap_choice = 0;
    std::cin >> fill_hashmap_choice;

    switch (fill_hashmap_choice)
    {
    case 1:
        fill_hashmap_sample_data(books);
        break;
    case 2:
        break;
    default:
        std::cout << "Неккоректный ввод!\n";
        return;
    }

    while (true)
    {
        std::cout << "========================================\n"
                  << "1 - Вывести таблицу\n"
                  << "2 - Вставить запись\n"
                  << "3 - Найти запись по isbn\n"
                  << "4 - Удалить запись по isbn\n"
                  << "5 - Удалить запись по индексу в таблице\n"
                  << "6 - Выход\n";
        int action_choice = 0;
        std::cin >> action_choice;
        std::cout << "========================================\n";

        if (action_choice == 1)
        {
            std::cout << (*books);
        }
        else if (action_choice == 2)
        {
            std::cout << "Введите isbn, автора книги и её название (через пробел)\n";
            book b;
            std::cin >> b;
            size_t index = books->insert(b);
            std::cout << "Книга была вставлена по индексу " << index << '\n';
        }
        else if (action_choice == 3)
        {
            std::cout << "Введите isbn: ";
            ull isbn = 0;
            std::cin >> isbn;

            int index = books->search(isbn);
            if (index == -1)
            {
                std::cout << "Книга не найдена\n";
            }
            else
            {
                std::cout << (*books->get(index)) << std::endl;
            }
        }
        else if (action_choice == 4)
        {
            std::cout << "Введите isbn: ";
            ull isbn = 0;
            std::cin >> isbn;

            bool is_deleted = books->remove_by_isbn(isbn);
            if (is_deleted)
            {
                std::cout << "Книга была успешно удалена\n";
            }
            else
            {
                std::cout << "Книга не была удалена (не найдена)\n";
            }
        }
        else if (action_choice == 5)
        {
            std::cout << "Введите индекс: ";
            size_t index = 0;
            std::cin >> index;

            bool is_deleted = books->remove_by_index(index);
            if (is_deleted)
            {
                std::cout << "Книга была успешно удалена\n";
            }
            else
            {
                std::cout << "Книга не была удалена (не найдена)\n";
            }
        }
        else if (action_choice == 6)
        {
            return;
        }
        else
        {
            std::cout << "Неккоректный ввод!\n";
            return;
        }
    }
}

void run_tests()
{
    book_hashmap* books = new book_hashmap();

    ull isbn1 = 123456789012;
    ull isbn2 = 987654321098;
    book b1(isbn1, "test 1", "test 1");
    book b2(isbn2, "test 2", "test 2");
    int iterations = 10;

    std::cout << "Тест вставок с коллизиями\n";
    for (int i = 0; i < iterations; i++)
    {
        books->insert(b1);
        books->insert(b2);
    }
    std::cout << (*books);

    std::cout << "\nТест поиска записей с коллизиями\n";
    std::cout << isbn1 << " <-- " << books->search(isbn1) << '\n';
    std::cout << isbn2 << " <-- " << books->search(isbn2) << '\n';

    std::cout << "\nТест удаления записей с коллизиями\n";
    bool is_deleted_1 = books->remove_by_isbn(isbn1);
    bool is_deleted_2 = books->remove_by_isbn(isbn2);
    std::cout << isbn1 << " --- "
              << (is_deleted_1 ? "Удалено" : "Не удалено") << '\n';
    std::cout << isbn1 << " --- "
              << (is_deleted_2 ? "Удалено" : "Не удалено") << '\n';

    std::cout << "\nПовторный тест поиска записей с коллизиями\n";
    std::cout << isbn1 << " <-- " << books->search(isbn1) << '\n';
    std::cout << isbn2 << " <-- " << books->search(isbn2) << '\n';

    std::cout << "\nТест изменения размера\n";
    std::cout << "Старый размер: " << books->hashmap_size() << '\n';
    size_t target_size = books->hashmap_size() * 10;
    for (int i = 0; i < target_size; i++)
    {
        books->insert(b1);
    }
    std::cout << "Новый размер: " << books->hashmap_size() << '\n';

    std::cout << "\nПовторный тест поиска записей в новой таблице\n";
    std::cout << isbn1 << " <-- " << books->search(isbn1) << '\n';
    std::cout << isbn2 << " <-- " << books->search(isbn2) << '\n';
}

int main()
{
    std::cout << "1 - Запустить пользовательский интерфейс\n"
              << "2 - Запустить тестирование\n"
              << "3 - Выход\n";
    int mode_choice = 0;
    std::cin >> mode_choice;

    switch (mode_choice)
    {
    case 1:
        run_shell();
        break;
    case 2:
        run_tests();
        break;
    case 3:
        break;
    default:
        std::cout << "Неккоректный ввод!\n";
        break;
    }

    return 0;
}
#include <iostream>
#include "bin_tree.h"

int main()
{
    bin_tree<double> t;
    
    while (true)
    {
        // Текстовый интерфейс пользователя
        std::cout << "1 - Вставить элементы в дерево\n"
                  << "2 - Вывести прямой обход дерева\n"
                  << "3 - Вывести симметричный обход дерева\n"
                  << "4 - Найти среднее арифметическое всех узлов\n"
                  << "5 - Найти длину пути от корня до заданного значения\n"
                  << "6 - Вывести дерево\n"
                  << "7 - Выход\n";
        int choice = 0;
        std::cin >> choice;

        if (choice == 1) // Вставить элементы в дерево
        {
            std::cout << "Введите элементы (через пробел): ";

            double value = 0.0;
            char buff = 0;

            // Считывание значений до получения символа '\n'
            buff = std::cin.get();
            while (true)
            {
                buff = std::cin.get();
                // Пропуск пробелов
                while (buff == ' ' && std::cin.good())
                {
                    buff = std::cin.get();
                }
                // При получении '\n' ввод завершается
                if (buff == '\n')
                {
                    break;
                }
                std::cin.putback(buff);

                std::cin >> value;
                t.insert(value);
            }

            std::cout << "Дерево:\n";
            t.print();
        }
        else if (choice == 2) // Вывести прямой обход дерева
        {
            std::cout << "Результат: ";
            t.print_preorder();
            std::cout << '\n';
        }
        else if (choice == 3) // Вывести симметричный обход дерева
        {
            std::cout << "Результат: ";
            t.print_inorder();
            std::cout << '\n';
        }
        else if (choice == 4) // Найти среднее арифметическое всех узлов
        {
            std::cout << "Результат: " << t.average() << '\n';
        }
        else if (choice == 5) // Найти длину пути от корня до заданного значения
        {
            std::cout << "Введите искомое значение: ";
            double value = 0.0;
            std::cin >> value;

            std::cout << "Результат: " << t.depth(value) << '\n';
        }
        else if (choice == 6) // Вывести дерево
        {
            std::cout << "Дерево:\n";
            t.print();
        }
        else if (choice == 7) // Выход
        {
            break;
        }
        else
        {
            std::cout << "Некорректный ввод!\n";
        }

        std::cout << "============================================================\n";
    }

    return 0;
}
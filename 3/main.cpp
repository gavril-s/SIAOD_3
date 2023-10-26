#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <chrono>

// Строит префикс-таблицу для КМП
std::vector<int> pre_kmp(std::string pattern)
{
	std::vector<int> pie(pattern.length(), 0);
	int k = 0;

	for (int i = 1; i < pattern.length(); i++)
	{
		while (k > 0 && pattern[k] != pattern[i])
		{
			k = pie[k - 1];
		}

		if (pattern[k] == pattern[i])
		{
			k++;
		}

		pie[i] = k;
	}
	
	return pie;
}

// Реализует КМП (алгоритм Кнута-Морриса-Пратта)
std::vector<int> kmp(std::string text, std::string pattern, int& comps)
{
    std::vector<int> res;
	std::vector<int> pie = pre_kmp(pattern);
	int k = 0;

	for (int i = 0; i < text.length(); i++)
	{
		while (k > 0 && pattern[k] != text[i])
        {
            comps++;
			k = pie[k - 1];
        }

        comps++;
		if (pattern[k] == text[i])
        {
			k++;
        }

		if (k == pattern.length())
		{
			res.push_back(i - pattern.length() + 1);
			k = pie[k - 1];
		}
	}

    return res;
}

// "Наивный" поиск, то есть простой перебор всех вариантов
std::vector<int> simple_search(std::string text, std::string pattern, int& comps)
{
    std::vector<int> res;

    for (int i = 0; i < text.length() - pattern.length() + 1; i++)
    {
        bool fits = true;
        for (int j = 0; j < pattern.length(); j++)
        {
            comps++;
            if (pattern[j] != text[i + j])
            {
                fits = false;
                break;
            }
        }

        if (fits)
        {
            res.push_back(i);
        }
    }

    return res;
}

// Решение 1 задания, удаляет слова-дубликаты из текста
std::string remove_duplicates(std::string text, int& comps)
{
    std::string res;
    std::string current_word;

    text.push_back(' ');
    for (int i = 0; i < text.length(); i++)
    {
        current_word.push_back(text[i]);
        if (text[i] == ' ')
        {
            std::vector<int> search_res = kmp(res, current_word, comps);
            if (search_res.size() == 0)
            {
                res += current_word;
            }
            current_word.clear();
        }
    }

    res.pop_back();
    return res;
}

// Решение 2 задания, удаляет все вхождения заданного слова
std::string remove_word(std::string text, std::string word, int& comps)
{
    text.push_back(' ');
    word.push_back(' ');

    std::vector<int> search_res = kmp(text, word, comps);
    for (int i = 0; i < search_res.size(); i++)
    {
        int begin_ind = search_res[i] - i * word.length();
        int end_ind = begin_ind + word.length();
        text.erase(text.begin() + begin_ind, text.begin() + end_ind);
    }

    text.pop_back();
    return text;
}

// Генерирует строку из случайных символов заданной длины
std::string random_string(int length) {
    const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::string res;
    for (int i = 0; i < length; i++)
    {
        res += charset[std::rand() % (sizeof(charset) - 1)];
    }
    
    return res;
}

// Тестирует производительность КМП и "наивного" алгоритма
// на строках и образцах различной длины,
// генерируемых функцией random_string
void run_tests()
{
    const int min_text_size = 1000;
    const int max_text_size = 1000000;
    const int text_size_mult = 10;
    const int runs_per_size = 5; 

    std::cout << "TEXT\tPATTERN\tFOUND\tCOMPS\tTIME\tCOMPS\tTIME\n";

    for (int text_size = min_text_size; text_size <= max_text_size; text_size *= text_size_mult)
    {
        int pattern_size_step = text_size / runs_per_size;
        for (int pattern_size = pattern_size_step;
             pattern_size <= text_size;
             pattern_size += pattern_size_step)
        {
            std::string text = random_string(text_size);
            std::string pattern;
            int comps = 0;

            int pattern_start_ind = std::rand() % (text_size - pattern_size + 1);
            for (int i = 0; i < pattern_size; i++)
            {
                pattern += text[pattern_start_ind + i];
            }

            // Запуск КМП на образце, который взят из строки
            auto start = std::chrono::high_resolution_clock().now();
            std::vector<int> kmp_res = kmp(text, pattern, comps);
            auto stop = std::chrono::high_resolution_clock().now();
            auto kmp_duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
            int kmp_comps = comps;
            
            // Запуск "наивного" поиска на образце, который взят из строки
            comps = 0;
            start = std::chrono::high_resolution_clock().now();
            std::vector<int> simple_res = simple_search(text, pattern, comps);
            stop = std::chrono::high_resolution_clock().now();
            auto simple_duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
            int simple_comps = comps;

            // Вывод результатов
            std::cout << text_size << '\t' << pattern_size << '\t' << (int)(kmp_res.size() != 0)
                      << '\t' << kmp_comps << '\t' << kmp_duration 
                      << '\t' << simple_comps << '\t' << simple_duration << '\n';

            // Образец - случайная строка (скроее всего не будет найдена)
            pattern = random_string(pattern_size);
            comps = 0;

            // Запуск КМП на случайном образце
            start = std::chrono::high_resolution_clock().now();
            kmp_res = kmp(text, pattern, comps);
            stop = std::chrono::high_resolution_clock().now();
            kmp_duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
            kmp_comps = comps;

            // Запуск "наивного" поиска на случайном образце
            comps = 0;
            start = std::chrono::high_resolution_clock().now();
            simple_res = simple_search(text, pattern, comps);
            stop = std::chrono::high_resolution_clock().now();
            simple_duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
            simple_comps = comps;

            // Вывод результатов
            std::cout << text_size << '\t' << pattern_size << '\t' << (int)(kmp_res.size() != 0)
                      << '\t' << kmp_comps << '\t' << kmp_duration 
                      << '\t' << simple_comps << '\t' << simple_duration << '\n';
        }
    }
}

// Основная функция программы
int main()
{
    std::srand(time(NULL));

    // Текстовый интерфейс пользователя
    while (true)
    {
        // Меню 
        std::cout << "1 - Удалить из предложения все слова, встретившиеся более одного раза\n"
                  << "2 - Удалить из предложения все вхождения заданного слова\n"
                  << "3 - Запустить тестирование\n"
                  << "4 - Выход\n";
        int choice = 0;
        std::cin >> choice;
        std::cin.get();

        if (choice == 1) // Удалить из предложения все слова, встретившиеся более одного раза
        {
            std::cout << "Введите предложение: ";
            std::string text;
            std::getline(std::cin, text);

            int comps = 0;
            std::cout << "Результат: " << remove_duplicates(text, comps) << '\n'
                      << "Количество сравнений: " << comps << "\n\n";
        }
        else if (choice == 2) // Удалить из предложения все вхождения заданного слова
        {
            std::string text, word;

            std::cout << "Введите предложение: ";
            std::getline(std::cin, text);

            std::cout << "Введите слово: ";
            std::getline(std::cin, word);

            int comps = 0;
            std::cout << "Результат: " << remove_word(text, word, comps) << '\n'
                      << "Количество сравнений: " << comps << "\n\n";
        }
        else if (choice == 3) // Запустить тестирование
        {
            run_tests();
        }
        else if (choice == 4) // Выход
        {
            break;
        }
        else
        {
            std::cout << "Некорректный ввод!\n\n";
        }
    }

	return 0;
}
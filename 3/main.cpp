#include <iostream>
#include <string>
#include <vector>

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

std::vector<int> kmp(std::string text, std::string pattern)
{
    std::vector<int> res;
	std::vector<int> pie = pre_kmp(pattern);
	int k = 0;

	for (int i = 0; i < text.length(); i++)
	{
		while (k > 0 && pattern[k] != text[i])
        {
			k = pie[k - 1];
        }

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

std::string remove_duplicates(std::string text)
{
    std::string res;
    std::string current_word;

    text.push_back(' ');
    for (int i = 0; i < text.length(); i++)
    {
        current_word.push_back(text[i]);
        if (text[i] == ' ')
        {
            std::vector<int> search_res = kmp(res, current_word);
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

std::string remove_word(std::string text, std::string word)
{
    text.push_back(' ');
    word.push_back(' ');

    std::vector<int> search_res = kmp(text, word);
    for (int i = 0; i < search_res.size(); i++)
    {
        int begin_ind = search_res[i] - i * word.length();
        int end_ind = begin_ind + word.length();
        text.erase(text.begin() + begin_ind, text.begin() + end_ind);
    }

    text.pop_back();
    return text;
}

int main()
{
    while (true)
    {
        std::cout << "1 - Удалить из предложения все слова, встретившиеся более одного раза\n"
                  << "2 - Удалить из предложения все вхождения заданного слова\n"
                  << "3 - Выход\n";
        int choice = 0;
        std::cin >> choice;
        std::cin.get();

        if (choice == 1)
        {
            std::cout << "Введите предложение: ";
            std::string text;
            std::getline(std::cin, text);

            std::cout << "Результат: " << remove_duplicates(text) << "\n\n";
        }
        else if (choice == 2)
        {
            std::string text, word;

            std::cout << "Введите предложение: ";
            std::getline(std::cin, text);

            std::cout << "Введите слово: ";
            std::getline(std::cin, word);

            std::cout << "Результат: " << remove_word(text, word) << "\n\n";
        }
        else if (choice == 3)
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
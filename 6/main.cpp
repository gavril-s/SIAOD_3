#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <regex>
#include <chrono>
#include <cstdlib>
#include <bitset>
#include <queue>
#include <map>
#include <unordered_map>
#include <locale>

using namespace std::chrono;
using namespace std;

// Структура для представления символа, его вероятности и кода
struct SymbolNode
{
    char symbol;        // Символ
    double probability; // Вероятность символа
    string code;        // Код символа
};

// Функция для сравнения символов по вероятности в убывающем порядке
bool CompareSymbols(SymbolNode a, SymbolNode b)
{
    return a.probability > b.probability;
}

// Рекурсивная функция для генерации кодов Шеннона-Фано
void ShannonFanoGenerate(int begin, int end, vector<SymbolNode>& frequencyTable)
{
    // Если разность индексов равна 1, завершаем выполнение функции
    if (end - begin == 1)
    {
        return;
    }

    int separator = begin + 1; // Устанавливаем разделитель
    double sumLeft = frequencyTable[begin].probability; // Сумма вероятностей слева
    double sumRight = 0; // Сумма вероятностей справа

    // Считаем сумму вероятностей справа от разделителя
    for (int i = separator; i < end; i++)
    {
        sumRight += frequencyTable[i].probability;
    }

    // Пока сумма вероятностей слева меньше суммы вероятностей справа
    while (separator < end - 1 && sumLeft < sumRight)
    {
        sumLeft += frequencyTable[separator].probability; // Добавляем вероятность элемента к сумме слева
        separator++; // Сдвигаем разделитель
        sumRight -= frequencyTable[separator].probability; // Убираем вероятность элемента из суммы справа
    }

    // Добавляем к коду символов слева '0', справа '1'
    for (int i = begin; i < separator; i++)
    {
        frequencyTable[i].code += "0";
    }
    for (int i = separator; i < end; i++)
    {
        frequencyTable[i].code += "1";
    }

    // Рекурсивно вызываем функцию для левой и правой части таблицы
    ShannonFanoGenerate(begin, separator, frequencyTable); // Левая часть
    ShannonFanoGenerate(separator, end, frequencyTable);   // Правая часть
}

// Функция для декодирования текста
string DecodeShannonFano(vector<SymbolNode>& frequencyTable, string encodedText)
{
    string text = "";
    while (!encodedText.empty())
    {
        for (auto& symbol : frequencyTable)
        {
            // Проверяем, начинается ли закодированный текст с кода символа
            if (encodedText.rfind(symbol.code, 0) == 0)
            {
                text += symbol.symbol;
                encodedText.erase(0, symbol.code.size());
                break;
            }
        }
    }
    return text;
}

// Основная функция для работы с кодами Шеннона-Фано
void ShannonFanoMain(string text)
{
    map<char, int> symbolFrequencies; // Карта для хранения частот каждого символа
    for (char ch : text)
    {
        symbolFrequencies[ch]++;
    }

    // создание таблицы символов
    vector<SymbolNode> frequencyTable;
    for (auto it : symbolFrequencies)
    {
        SymbolNode node;
        node.symbol = it.first;
        node.probability = (double)it.second / text.length();
        frequencyTable.push_back(node);
    }

    sort(frequencyTable.begin(), frequencyTable.end(), CompareSymbols);

    ShannonFanoGenerate(0, frequencyTable.size(), frequencyTable);

    float totalBitCount = 0;
    for (SymbolNode symbol : frequencyTable)
    {
        int totalCount = symbol.probability * text.length();
        totalBitCount += totalCount * symbol.code.length();
    }
    
    string encodedText = "";
    for (char ch : text)
    {
        for (SymbolNode symbol : frequencyTable)
        {
            if (ch == symbol.symbol)
            {
                encodedText += symbol.code;
                break;
            }
        }
    }

    cout << "Закодированный текст: " << encodedText << endl;

    string decodedText = DecodeShannonFano(frequencyTable, encodedText);
    cout << "Декодированный текст: " << decodedText << endl;

    cout << "Количество символов в тексте: " << text.length() << endl;
    cout << "Итоговый вес закодированного текста в битах: " << int(totalBitCount) << " бит" << endl;
    float totalBitText = text.length() * 8;
    cout << "Вес изначального текста в битах: " << int(totalBitText) << " бит" << endl;
    float compressionPercentage = 100 * totalBitCount / totalBitText;
    cout << "Процент сжатия: " << 100 - compressionPercentage << "%" << endl;
}

// Структура для представления узла в дереве Хаффмана
struct HuffmanNode
{
    char data;             // Символ узла
    int frequency;         // Частота символа в тексте
    HuffmanNode* left;     // Указатель на левого потомка
    HuffmanNode* right;    // Указатель на правого потомка

    // Конструктор для удобного создания узла с данными и частотой
    HuffmanNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// Функтор для сравнения узлов в приоритетной очереди по частоте
struct CompareNodes
{
    bool operator()(HuffmanNode* left, HuffmanNode* right)
    {
        return left->frequency > right->frequency;
    }
};

// Рекурсивная функция для генерации кодов Хаффмана
void generateCodes(HuffmanNode* root, string code, unordered_map<char, string>& codes)
{
    if (root)
    {
        if (!root->left && !root->right)
        {
            codes[root->data] = code; // Если узел является листом, добавляем код в словарь
        }
        generateCodes(root->left, code + "0", codes);  // Рекурсивно обрабатываем левое поддерево с добавлением "0" к текущему коду
        generateCodes(root->right, code + "1", codes); // Рекурсивно обрабатываем правое поддерево с добавлением "1" к текущему коду
    }
}

// Функция для построения дерева Хаффмана и получения кодов
HuffmanNode* buildHuffmanTree(string text, unordered_map<char, string>& codes)
{
    unordered_map<char, int> frequencyMap;
    for (char ch : text)
    {
        frequencyMap[ch]++;
    }

    // Приоритетная очередь для узлов с приоритетом наименьшей частоты
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> minHeap;
    for (auto entry : frequencyMap)
    {
        HuffmanNode* node = new HuffmanNode(entry.first, entry.second);
        minHeap.push(node);
    }

    // Строим дерево Хаффмана
    while (minHeap.size() > 1)
    {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();

        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* mergedNode = new HuffmanNode('$', left->frequency + right->frequency);
        mergedNode->left = left;
        mergedNode->right = right;

        minHeap.push(mergedNode);
    }

    // Получаем коды Хаффмана
    HuffmanNode* root = minHeap.top();
    generateCodes(root, "", codes);

    return root;
}

// Функция для кодирования текста с использованием кодов Хаффмана
string encodeText(string text, unordered_map<char, string>& codes)
{
    string encodedText = "";
    for (char ch : text)
    {
        encodedText += codes[ch];
    }
    return encodedText;
}

// Функция для декодирования текста с использованием дерева Хаффмана
string decodeText(HuffmanNode* root, string encodedText)
{
    string decodedText = "";
    HuffmanNode* current = root;
    for (char bit : encodedText)
    {
        if (bit == '0')
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
        if (!current->left && !current->right)
        {
            decodedText += current->data;
            current = root;
        }
    }
    return decodedText;
}

// Основная функция для работы с алгоритмом Хаффмана
void huffmanMain(string text)
{
    unordered_map<char, string> codes;
    HuffmanNode* root = buildHuffmanTree(text, codes);

    // Закодировать текст
    string encodedText = encodeText(text, codes);

    // Расчет процента и коэффициента сжатия
    double originalSize = text.size() * 8.0; // каждый символ представлен 8 битами
    double compressedSize = encodedText.size();
    double compressionRatio = originalSize / compressedSize;
    double compressionPercentage = (1 - (compressedSize / originalSize)) * 100;

    // Декодировать текст
    string decodedText = decodeText(root, encodedText);

    // Вывод результатов
    cout << "Декодированный текст: " << decodedText << endl;
    cout << "Закодированный текст: " << encodedText << endl;
    cout << "Итоговый вес закодированного текста в битах: " << compressedSize << " бит" << endl;
    cout << "Вес изначального текста в битах: " << originalSize << " бит" << endl;
    cout << "Процент сжатия: " << compressionPercentage << "%" << endl;
    cout << "Коэффициент сжатия: " << compressionRatio << endl;
}


int main()
{
    string filename = "text.txt";
    ifstream inputFile(filename);
    string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    string textContent = "Сенькевич Гаврил Дмитриевич";

    int mode = 0;
    cout << "1 -- выполнить сжатие текстового файла алгоритмом Шеннона – Фано" << endl;
    cout << "2 -- выполнить сжатие строки (\"Сенькевич Гаврил Дмитриевич\") алгоритмом Хаффмана" << endl;
    cout << "3 -- выполнить сжатие текстового файла алгоритмом Хаффмана" << endl;
    cout << "0 -- завершить работу" << endl;

    cin >> mode;
    while (mode != 0)
    {
        if (mode == 1)
        {
            ShannonFanoMain(fileContent);
        }
        else if (mode == 2)
        {
            huffmanMain(textContent);
        }
        else if (mode == 3)
        {
            huffmanMain(fileContent);
        }
        else
        {
            break;
        }

        cout << "1 -- выполнить сжатие текстового файла алгоритмом Шеннона – Фано" <<endl;
        cout << "2 -- выполнить сжатие строки {Сенькевич Гаврил Дмитриевич} алгоритмом Хаффмана" <<endl;
        cout << "3 -- выполнить сжатие текстового файла алгоритмом Хаффмана" <<endl;
        cout << "0 -- завершить работу" <<endl;
        cin >> mode;
    }
}

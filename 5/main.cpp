#include <iostream>
#include <vector>
#include <queue>

// Класс, описывающий неориентированный граф
class graph
{
private:
    // Количество рёбер
    int edges = 0;
    // Количество вершин
    int vertices = 0;
    // Матрица смежности
    std::vector<std::vector<bool>> adjacency_matrix;

    // Всомогательная функция для print_euler
    // (выполняет основную работу)
    void print_euler_util(int start, std::vector<std::vector<bool>>& matrix)
    {
        // Цикл по всем вершинам
        for (int i = 0; i < vertices; i++)
        {
            // Если нашли смежную вершину с начальной
            if (matrix[start][i])
            {
                // Удаляем ребро между этой вершиной и начальной
                matrix[start][i] = false;
                matrix[i][start] = false;

                // Рекурсивно запускаем функцию от этой вершины
                print_euler_util(i, matrix);
            }
        }

        // Выводим начальную вершину
        std::cout << start << ' ';
    }

public:
    // Конструктор (создаёт матрицу смежности и заполняет её false)
    graph(int vertices) : adjacency_matrix(vertices)
    {
        this->vertices = vertices;
        for (std::vector<bool>& row : adjacency_matrix)
        {
            row = std::vector<bool>(vertices, false);
        }
    }

    // Вставляет ребро в граф
    void insert_edge(int first, int second)
    {
        if (first < 0 || first >= vertices ||
            second < 0 || second >= vertices)
        {
            return;
        }

        // Вставляем ребро first->second
        adjacency_matrix[first][second] = true;

        // Вставляем ребро second->first
        adjacency_matrix[second][first] = true;

        edges++;
    }

    // Выводит матрицу смежности 
    // 0 - false, 1 - true
    void print_adjacency_matrix()
    {
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                std::cout << (adjacency_matrix[i][j] ? 1 : 0) << ' ';
            }
            std::cout << '\n';
        }
    }

    // Выводит обход графа в ширину
    void print_bfs(int start)
    {
        if (start < 0 || start >= vertices)
        {
            return;
        }

        // Список посещённых вершин
        std::vector<bool> visited(vertices, false);
        // Очередь вершин на обработку
        std::queue<int> queue;

        // Помещаем в очередь начальную вершину
        queue.push(start);
        visited[start] = true;

        // Пока в очереди есть вершины
        while (!queue.empty())
        {
            // Берём первую вершину из очереди
            int current = queue.front();
            std::cout << current << ' ';

            // Цикл по всем вершинам
            for (int i = 0; i < vertices; i++)
            {
                // Если вершина смежна с текущей и не посещена
                if (adjacency_matrix[current][i] && !visited[i])
                {
                    // Отмечаем её посещённой и добавляем в очередь
                    visited[i] = true;
                    queue.push(i);
                }
            }

            // Удаляем текущую вершину из очереди
            queue.pop();
        }

        std::cout << '\n';
    }

    // Проверяет граф на связность
    bool is_connected()
    {
        if (vertices == 0)
        {
            return true;
        }

        // Список посещённых вершин
        std::vector<bool> visited(vertices, false);
        // Очередь вершин на обработку
        std::queue<int> queue;

        // Помещаем в очередь начальную вершину
        queue.push(0);
        visited[0] = true;

        // Пока в очереди есть вершины
        while (!queue.empty())
        {
            // Берём первую вершину из очереди
            int current = queue.front();

            // Цикл по всем вершинам
            for (int i = 0; i < vertices; i++)
            {
                // Если вершина смежна с текущей и не посещена
                if (adjacency_matrix[current][i] && !visited[i])
                {
                    // Отмечаем её посещённой и добавляем в очередь
                    visited[i] = true;
                    queue.push(i);
                }
            }

            // Удаляем текущую вершину из очереди
            queue.pop();
        }

        // Цикл по всем вершинам
        for (int i = 0; i < visited.size(); i++)
        {
            // Если вершина не была посещена в ходе обхода
            if (!visited[i])
            {
                // Граф несвязный
                return false;
            }
        }

        // Если все вершины были посещены,
        // граф связный
        return true;
    }

    // Вычисляет степень вершины
    int vertex_degree(int vertex)
    {
        if (vertex < 0 || vertex >= vertices)
        {
            return -1;
        }

        int degree = 0;
        // Цикл по всем вершинам
        for (int i = 0; i < vertices; i++)
        {
            // Если вершина смежна с рассматриваемой
            if (adjacency_matrix[vertex][i])
            {
                // Увеличиваем степень на 1
                degree++;
            }
        }

        // Возвращаем степень
        return degree;
    }

    // Прооверяет наличие ейлерова цикла
    bool has_euler_cycle()
    {
        // Ейлеров цикл может существовать
        // только в связных графах
        if (!is_connected())
        {
            return false;
        }

        // Каждая вершина должна иметь
        // чётную степень
        for (int i = 0; i < vertices; i++)
        {
            if (vertex_degree(i) % 2 == 1)
            {
                return false;
            }
        }

        return true;
    }

    // Печатает ейлеров цикл
    void print_euler()
    {
        // Если в графе есть ейлеров цикл
        if (has_euler_cycle())
        {
            // Записываем матрицу смежности в отдельную переменную
            // (она будет изменяться)
            std::vector<std::vector<bool>> matrix = adjacency_matrix;
            // Вызываем вспомогательную функцию
            print_euler_util(0, matrix);
            std::cout << '\n';
        }
        else
        {
            std::cout << "В этом графе нет ейлерова цикла!\n";
        }
    }
};

int main()
{
    // Считываем количество вершин в графе
    std::cout << "Введите количество вершин в графе: ";
    int vertices = 0;
    std::cin >> vertices;

    // Создаём граф
    graph g(vertices);

    // Считываем рёбра графа
    std::cout << "Введите рёбра (в формате \"вершина1 вершина2\", нумерация вершин начинается с 0):\n";
    int first_vertex = 0, second_vertex = 0;
    char buffer = std::cin.get();
    // Цикл идёт пока не встретятся два перевода на новую
    // строку подряд
    while (true)
    {
        // Получаем один символ
        buffer = std::cin.get();

        // Пропускаем пробелы
        while (buffer == ' ' && std::cin.good())
        {
            buffer = std::cin.get();
        }

        // Выходим из цикла если 
        // в потоке находятся
        // два '\n' подряд
        if (buffer == '\n')
        {
            buffer = std::cin.get();
            if (buffer == '\n')
            { 
                break;
            }
        }
        // Возвращаем символ в поток
        std::cin.putback(buffer);

        // Считываем пару вершин
        std::cin >> first_vertex >> second_vertex;
        // Вставляем ребро
        g.insert_edge(first_vertex, second_vertex);
    }

    // Выводим матрицу смежности получившегося графа
    std::cout << "Матрица смежности графа:\n";
    g.print_adjacency_matrix();
    std::cout << '\n';

    while (true)
    {
        // Выводим текстовое меню
        std::cout << "1 - Вывести матрицу смежности\n"
                  << "2 - Вывести обход в ширину\n"
                  << "3 - Вывести эйлеров цикл\n"
                  << "4 - Выход\n";
        int choice = 0;
        std::cin >> choice;

        if (choice == 1) // Вывести матрицу смежности
        {
            std::cout << "Результат:\n";
            g.print_adjacency_matrix();
        }
        else if (choice == 2) // Вывести обход в ширину
        {
            std::cout << "Введите вершину, с которой вы хотите начать обход: ";
            int start = 0;
            std::cin >> start;
            std::cout << "Результат: ";
            g.print_bfs(start);
        }
        else if (choice == 3) // Вывести эйлеров цикл
        {
            std::cout << "Результат: ";
            g.print_euler();
        }
        else if (choice == 4) // Выход
        {
           break;
        }
        else
        {
            std::cout << "Некорректный ввод!\n";
        }
        std::cout << '\n';
    }

    return 0;
}
#include <iostream>
#include <vector>

bool next_permutation(std::vector<int>& v)
{
    int j = v.size() - 2;
    while (j != -1 && v[j] >= v[j + 1]) 
    {
        j--;
    }
    if (j == -1)
    {
        // Больше перестановок нет
        return false;
    }

    int k = v.size() - 1;
    while (v[j] >= v[k])
    {
        k--;
    }
    std::swap(v[j], v[k]);

    int l = j + 1;
    // Сортируем оставшуюся часть последовательности
    int r = v.size() - 1; 
    while (l < r)
    {
        std::swap(v[l++], v[r--]);
    }

    return true;
}

// Класс, описывающий неориентированный взвешенный граф
class graph
{
private:
    // Количество рёбер
    int edges = 0;
    // Количество вершин
    int vertices = 0;
    // Матрица смежности
    std::vector<std::vector<int>> adjacency_matrix;
public:
    // Конструктор (создаёт матрицу смежности и заполняет её false)
    graph(int vertices) : adjacency_matrix(vertices)
    {
        this->vertices = vertices;
        for (std::vector<int>& row : adjacency_matrix)
        {
            row = std::vector<int>(vertices, -1);
        }
    }

    // Вставляет ребро в граф
    void insert_edge(int first, int second, int weight)
    {
        if (first < 0 || first >= vertices ||
            second < 0 || second >= vertices)
        {
            return;
        }

        // Вставляем ребро first->second
        adjacency_matrix[first][second] = weight;

        // Вставляем ребро second->first
        adjacency_matrix[second][first] = weight;

        edges++;
    }

    // Выводит матрицу смежности 
    void print_adjacency_matrix()
    {
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                std::cout << adjacency_matrix[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }

    // Решает задачу полным перебором
    void solve_salesman_dumb()
    {
        std::vector<int> vertices_indices(vertices, 0);
        for (int i = 0; i < vertices_indices.size(); i++)
        {
            vertices_indices[i] = i;
        }

        int min_distance = -1;
        do
        {
            int distance = 0;
            bool path_exists = true;
            for (int i = 0; i < vertices_indices.size() - 1; i++)
            {
                int to_add = adjacency_matrix[i][i + 1];
                if (to_add == -1)
                {
                    path_exists = false;
                    break;
                }
                else 
                {
                    distance += to_add
                } 
            }
            distance += adjacency_matrix[vertices_indices.size() - 1][0];

            if (path_exists && (min_distance == -1 || distance < min_distance))
            {
                min_distance = distance;
            }
        } while (next_permutation(vertices_indices))

        return min_distance;
    }

    void solve_salesman_smart()
    {
        std::vector<std::vector<int>> matrix(adjacency_matrix);

        

        int min_sum = 0;
        for (int i = 0; i < vertices; i++)
        {
            int min_element = matrix[i][0];
            for (int j = 1; j < vertices; j++)
            {
                if (matrix[i][j] < min_element)
                {
                    min_element = matrix[i][j];
                }
            }
            for (int j = 0; j < vertices; j++)
            {
                matrix[i][j] -= min_element;
            }

            min_sum += min_element;

            int min_element = matrix[0][i];
            for (int j = 1; j < vertices; j++)
            {
                if (matrix[j][i] < min_element)
                {
                    min_element = matrix[j][i];
                }
            }
            for (int j = 0; j < vertices; j++)
            {
                matrix[j][i] -= min_element;
            }

            min_sum += min_element;
        }
    }
};

int main()
{
    std::cout << "Введите количество городов: ";
    int cities_num = 0;
    std::cin >> cities_num;

    graph cities(cities_num);
    
    std::cout << "Введите :\n";
    int first = 0, second = 0, distance = 0;
    while (std::cin >> first >> second >> distance)
    {
        cities.insert_edge(first, second, distance);
    }

    cities.print_adjacency_matrix();

    cities.solve_salesman_dumb();
    cities.solve_salesman_smart();

    return 0;
}
#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

// Вершина бинарного дерева поиска
template <typename T>
struct bin_tree_node
{
    // Значение вершины
    T val_ = T();
    // Родительская вершина
    bin_tree_node* parent_      = nullptr;
    // Левая дочерняя вершина
    bin_tree_node* left_child_  = nullptr;
    // Правая дочерняя вершина
    bin_tree_node* right_child_ = nullptr;

    bin_tree_node(T val,
                  bin_tree_node* parent      = nullptr,
                  bin_tree_node* left_child  = nullptr, 
                  bin_tree_node* right_child = nullptr)
    : val_(val), parent_(parent), left_child_(left_child),
      right_child_(right_child) {}
};

// Бинарное дерево поиска
template <typename T>
class bin_tree
{
private:
    // Корень дерево
    bin_tree_node<T>* root_ = nullptr;

    // Функция, удаляющая поддерево рекурсивно (вызывается из деструктора)
    void del_tree(bin_tree_node<T>* node);

    // Вставка нового значения в поддерево
    bin_tree_node<T>* insert(bin_tree_node<T>* parent, T val);
    // Вывод прямого обхода поддерева
    void print_preorder(bin_tree_node<T>* node);
    // Вывод симметричного обхода поддерева
    void print_inorder(bin_tree_node<T>* node);
    // Длина пути от заданной вершины до заданного значения
    int depth(bin_tree_node<T>* node, T val, int current_depth = 0);
    // Высота поддерева (от заданной вершины)
    size_t height(bin_tree_node<T>* node);

    // Сумма значений всех вершин поддерева
    T sum(bin_tree_node<T>* node);
    // Подсчёт вершин в поддереве
    size_t count(bin_tree_node<T>* node);

public:
    // Деструктор
    ~bin_tree();

    // Вставка нового значения в дерево
    bin_tree_node<T>* insert(T val);
    // Вывод прямого обхода дерева
    void print_preorder();
    // Вывод симметричного обхода дерева
    void print_inorder();
    // Длина пути от корня до заданного значения
    int depth(T val);
    // Высота дерева
    size_t height();

    // Среднее арифметическое по всем вершинам
    T average();
    // Вывод дерева (форматированный)
    void print(size_t value_length = 0);
};

// Функция, удаляющая поддерево рекурсивно (вызывается из деструктора)
template <typename T>
void bin_tree<T>::del_tree(bin_tree_node<T>* node)
{
    if (node == nullptr) return;
    del_tree(node->left_child_);
    del_tree(node->right_child_);
    delete node;
}

// Вставка нового значения в поддерево
template <typename T>
bin_tree_node<T>* bin_tree<T>::insert(bin_tree_node<T>* parent, T val)
{
    if (parent == nullptr)
    {
        if (root_ == nullptr)
        {
            root_ = new bin_tree_node<T>(val);
            return root_;
        }
        return nullptr;
    }

    if (val < parent->val_)
    {
        if (parent->left_child_ == nullptr)
        {
            bin_tree_node<T>* new_node = new bin_tree_node<T>(val, parent);
            parent->left_child_ = new_node;
            return new_node;
        }
        else
        {
            return insert(parent->left_child_, val);
        }
    }
    else
    {
        if (parent->right_child_ == nullptr)
        {
            bin_tree_node<T>* new_node = new bin_tree_node<T>(val, parent);
            parent->right_child_ = new_node;
            return new_node;
        }
        else
        {
            return insert(parent->right_child_, val);
        }
    }
}

// Вывод прямого обхода поддерева
template <typename T>
void bin_tree<T>::print_preorder(bin_tree_node<T>* node)
{
    if (node == nullptr) return;
    std::cout << node->val_ << ' ';
    print_preorder(node->left_child_);   
    print_preorder(node->right_child_);
}

// Вывод симметричного обхода поддерева
template <typename T>
void bin_tree<T>::print_inorder(bin_tree_node<T>* node)
{
    if (node == nullptr) return;
    print_inorder(node->left_child_);
    std::cout << node->val_ << ' ';
    print_inorder(node->right_child_);
}

// Длина пути от заданной вершины до заданного значения
template <typename T>
int bin_tree<T>::depth(bin_tree_node<T>* node, T val, int current_depth)
{
    if (node == nullptr)
    {
        return -1;
    }

    if (val == node->val_)
    {
        return current_depth;
    }    
    else if (val < node->val_)
    {
        return depth(node->left_child_, val, current_depth + 1);
    }
    else
    {
        return depth(node->right_child_, val, current_depth + 1);
    }
}

// Высота поддерева (от заданной вершины)
template <typename T>
size_t bin_tree<T>::height(bin_tree_node<T>* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    
    return 1 + std::max(
        height(node->left_child_),
        height(node->right_child_)
    );
}

// Сумма значений всех вершин поддерева
template <typename T>
T bin_tree<T>::sum(bin_tree_node<T>* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return node->val_ + sum(node->left_child_) + sum(node->right_child_);
}

// Подсчёт вершин в поддереве
template <typename T>
size_t bin_tree<T>::count(bin_tree_node<T>* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return 1 + count(node->left_child_) + count(node->right_child_);
}

// Деструктор
template <typename T>
bin_tree<T>::~bin_tree()
{
    del_tree(root_);
}

// Вставка нового значения в дерево
template <typename T>
bin_tree_node<T>* bin_tree<T>::insert(T val)
{
    return insert(root_, val);
}

// Вывод прямого обхода дерева
template <typename T>
void bin_tree<T>::print_preorder()
{
    print_preorder(root_);
}

// Вывод симметричного обхода дерева
template <typename T>
void bin_tree<T>::print_inorder()
{
    print_inorder(root_);
}

// Среднее арифметическое по всем вершинам
template <typename T>
T bin_tree<T>::average()
{
    return sum(root_) / count(root_);
}

// Длина пути от корня до заданного значения
template <typename T>
int bin_tree<T>::depth(T val)
{
    return depth(root_, val);
}

// Высота дерева
template <typename T>
size_t bin_tree<T>::height()
{
    return height(root_);
}

// Вывод дерева (форматированный)
template <typename T>
void bin_tree<T>::print(size_t value_length)
{
    if (root_ == nullptr) return;

    std::vector<bin_tree_node<T>*> layer {root_};
    bool null_layer = false;
    int shift_length = ((1 << height()) * (value_length + 2) - value_length) / 2;

    while (!null_layer)
    {
        null_layer = true;
        std::vector<bin_tree_node<T>*> next_layer;

        std::string shift;
        for (int i = 0; i < shift_length; i++)
        {
            shift += ' ';
        }

        std::cout << shift;
        for (bin_tree_node<T>* node : layer)
        {
            std::cout << std::setw(value_length);    
            if (node == nullptr)
            {
                std::cout << ' ';
            }
            else
            {
                null_layer = false;
                std::cout << node->val_;
            }
            std::cout << shift << shift;

            if (node != nullptr)
            {
                next_layer.push_back(node->left_child_);
                next_layer.push_back(node->right_child_);
            }
            else
            {
                next_layer.push_back(nullptr);
                next_layer.push_back(nullptr);
            }
        }
        std::cout << std::endl;

        shift_length = (2 * shift_length - value_length) / 4;
        layer = next_layer;
    }
}
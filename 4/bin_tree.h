#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

template <typename T>
struct bin_tree_node
{
    T val_ = T();
    bin_tree_node* parent_      = nullptr;
    bin_tree_node* left_child_  = nullptr;
    bin_tree_node* right_child_ = nullptr;

    bin_tree_node(T val,
                  bin_tree_node* parent      = nullptr,
                  bin_tree_node* left_child  = nullptr, 
                  bin_tree_node* right_child = nullptr)
    : val_(val), parent_(parent), left_child_(left_child),
      right_child_(right_child) {}
};

template <typename T>
class bin_tree
{
private:
    bin_tree_node<T>* root_ = nullptr;

    void del_tree(bin_tree_node<T>* node);

    bin_tree_node<T>* insert(bin_tree_node<T>* parent, T val);
    void print_inorder(bin_tree_node<T>* node);
    void print_preorder(bin_tree_node<T>* node);
    int depth(bin_tree_node<T>* node, T val);
    size_t height(bin_tree_node<T>* node);

    T sum(bin_tree_node<T>* node);
    size_t count(bin_tree_node<T>* node);

public:
    ~bin_tree();

    bin_tree_node<T>* insert(T val);
    void print_inorder();
    void print_preorder();
    int depth(T val);
    size_t height();

    T average();
    void print(size_t value_length = 3);
};

template <typename T>
void bin_tree<T>::del_tree(bin_tree_node<T>* node)
{
    if (node == nullptr) return;
    del_tree(node->left_child_);
    del_tree(node->right_child_);
    delete node;
}

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

template <typename T>
void bin_tree<T>::print_inorder(bin_tree_node<T>* node)
{
    if (node == nullptr) return;
    print_inorder(node->left_child_);
    std::cout << node->val_ << std::endl;
    print_inorder(node->right_child_);
}

template <typename T>
void bin_tree<T>::print_preorder(bin_tree_node<T>* node)
{
    if (node == nullptr) return;
    std::cout << node->val_ << std::endl;
    print_preorder(node->left_child_);   
    print_preorder(node->right_child_);
}

template <typename T>
int depth(bin_tree_node<T>* node, T val)
{
    if (node == nullptr)
    {
        return -1;
    }

    if (node->val_ == val)
    {
        return 0;
    }    
    else if (node->val < val)
    {
        return 1 + depth(node->left_child_, val);
    }
    else
    {
        return 1 + depth(node->right_child_, val);
    }
}

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

template <typename T>
T bin_tree<T>::sum(bin_tree_node<T>* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return node->val_ + sum(node->left_child_) + sum(node->right_child_);
}

template <typename T>
size_t bin_tree<T>::count(bin_tree_node<T>* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return 1 + count(node->left_child_) + count(node->right_child_);
}

template <typename T>
bin_tree<T>::~bin_tree()
{
    del_tree(root_);
}

template <typename T>
bin_tree_node<T>* bin_tree<T>::insert(T val)
{
    return insert(root_, val);
}

template <typename T>
void bin_tree<T>::print_inorder()
{
    print_inorder(root_);
}

template <typename T>
void bin_tree<T>::print_preorder()
{
    print_preorder(root_);
}

template <typename T>
T bin_tree<T>::average()
{
    return sum(root_) / count(root_);
}

template <typename T>
int bin_tree<T>::depth(T val)
{
    return depth(root_, val);
}

template <typename T>
size_t bin_tree<T>::height()
{
    return height(root_);
}

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
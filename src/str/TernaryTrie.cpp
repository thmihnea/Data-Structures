#include "TernaryTrie.h"
#include <iostream>

using namespace dsa;

template <typename T>
Node<T>::Node() : m_c('\0'), m_left(nullptr), m_right(nullptr), m_mid(nullptr), m_value(std::nullopt) {}

template <typename T>
Node<T>::Node(char c) : m_c(c), m_left(nullptr), m_right(nullptr), m_mid(nullptr), m_value(std::nullopt) {}

template <typename T>
Node<T>::~Node()
{
    delete this->m_left;
    delete this->m_right;
    delete this->m_mid;
}

template <typename T>
std::optional<T> Node<T>::value()
{
    return this->m_value;
}

template <typename T>
Node<T>* Node<T>::left()
{
    return this->m_left;
}

template <typename T>
Node<T>* Node<T>::right()
{
    return this->m_right;
}

template <typename T>
Node<T>* Node<T>::mid()
{
    return this->m_mid;
}

template <typename T>
void Node<T>::set_value(T value)
{
    this->m_value = value;
}

template <typename T>
char Node<T>::c()
{
    return this->m_c;
}

template <typename T>
void Node<T>::set_c(char c)
{
    this->m_c = c;
}

template <typename T>
void Node<T>::set_left(Node<T>* left)
{
    this->m_left = left;
}

template <typename T>
void Node<T>::set_right(Node<T>* right)
{
    this->m_right = right;
}

template <typename T>
void Node<T>::set_mid(Node<T>* mid)
{
    this->m_mid = mid;
}

template <typename T>
TernaryTrie<T>::TernaryTrie()
{
    this->m_root = nullptr;
}

template <typename T>
TernaryTrie<T>::~TernaryTrie()
{
    delete this->m_root;
}

template <typename T>
static Node<T>* put_helper(Node<T>* x, std::string key, T value, int d)
{
    char c = key.at(d);
    if (x == nullptr)
    {
        x = new Node<T>(c);
    }

    if (c < x->c()) x->set_left(put_helper(x->left(), key, value, d));
    else if (c > x->c()) x->set_right(put_helper(x->right(), key, value, d));
    else if (d < key.size() - 1) x->set_mid(put_helper(x->mid(), key, value, d + 1));
    else x->set_value(value);

    return x;
}

template <typename T>
void TernaryTrie<T>::put(std::string key, T value)
{
    this->m_root = put_helper(this->m_root, key, value, 0);
}

template <typename T>
static Node<T>* get_helper(Node<T>* x, std::string key, int d)
{
    if (x == nullptr) return nullptr;

    char c = key.at(d);

    if (c < x->c()) return get_helper(x->left(), key, d);
    else if (c > x->c()) return get_helper(x->right(), key, d);
    else if (d < key.size() - 1) return get_helper(x->mid(), key, d + 1);
    else return x;
}

template <typename T>
std::optional<T> TernaryTrie<T>::get(std::string key)
{
    Node<T>* node = get_helper(this->m_root, key, 0);
    if (node == nullptr) return std::nullopt;
    return node->value();
}

template <typename T>
bool TernaryTrie<T>::contains(std::string key)
{
    return this->get(key).has_value();
}

int main(int argc, char* argv[])
{
    auto trie = TernaryTrie<int>();
    trie.put("asd", 2);
    std::cout << trie.contains("asd");
}

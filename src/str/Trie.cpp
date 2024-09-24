#include "Trie.h"
#include <iostream>

using namespace dsa;

template <typename T, int R>
Node<T, R>::Node()
{
    this->m_next = new Node<T, R>*[r];
    for (int i = 0; i < r; i++)
    {
        this->m_next[i] = nullptr;
    }
}

template <typename T, int R>
Node<T, R>::Node(T value) : m_value(value)
{
    this->m_next = new Node<T, R>*[r];
}

template <typename T, int R>
Node<T, R>::~Node()
{
    for (int i = 0; i < r; i++)
    {
        if (this->m_next[i] != nullptr)
            delete this->m_next[i];
    }
    delete[] this->m_next;
}

template <typename T, int R>
std::optional<T> Node<T, R>::value()
{
    if (this->m_value.has_value()) return *this->m_value;
    return std::nullopt;
}

template <typename T, int R>
void Node<T, R>::set_value(T value)
{
    this->m_value = value;
}

template <typename T, int R>
Node<T, R>** Node<T, R>::next()
{
    return this->m_next;
}

template <typename T, int R>
Trie<T, R>::Trie()
{
    this->m_root = new Node<T, R>;
}

template <typename T, int R>
Trie<T, R>::~Trie()
{
    delete this->m_root;
}

template <typename T, int R>
static Node<T, R>* put_helper(Node<T, R>* x, std::string key, T value, int d)
{
    if (x == nullptr) x = new Node<T, R>;
    if (d == key.size())
    {
        x->set_value(value);
        return x;
    }
    char c = static_cast<unsigned char>(key.at(d));
    x->next()[c] = put_helper(x->next()[c], key, value, d + 1);
    return x;
}

template <typename T, int R>
void Trie<T, R>::put(std::string key, T value)
{
    this->m_root = put_helper(this->m_root, key, value, 0);
}

template <typename T, int R>
static Node<T, R>* get_helper(Node<T, R>* x, std::string key, int d)
{
    if (x == nullptr) return nullptr;
    if (d == key.size()) return x;
    char c = static_cast<unsigned char>(key.at(d));
    return get_helper(x->next()[c], key, d + 1);
}

template <typename T, int R>
std::optional<T> Trie<T, R>::get(std::string key)
{
    Node<T, R>* node = get_helper(this->m_root, key, 0);
    if (node == nullptr) return std::nullopt;
    if (node->value().has_value()) return *node->value();
    return std::nullopt;
}

template <typename T, int R>
bool Trie<T, R>::contains(std::string key)
{
    return this->get(key) != std::nullopt;
}

template <typename T, int R>
static void collect(Node<T, R>* x, std::string prefix, std::queue<std::string> &queue)
{
    if (x == nullptr) return;
    if (x->value().has_value()) queue.push(prefix);
    for (char c = 'a'; c < 'z'; c++)
        collect(x->next()[c], prefix + c, queue);
}

template <typename T, int R>
static int search(Node<T, R>* x, std::string key, int d, int length)
{
    if (x == nullptr) return length;
    if (x->value().has_value()) length = d;
    if (d == key.length()) return length;
    char c = key.at(d);
    return search(x->next()[c], key, d + 1, length);
}

template <typename T, int R>
std::queue<std::string> Trie<T, R>::keys()
{
    std::queue<std::string> queue;
    collect(this->m_root, "", queue);
    return queue;
}

template <typename T, int R>
std::queue<std::string> Trie<T, R>::keys_with_prefix(std::string prefix)
{
    std::queue<std::string> queue;
    Node<T, R>* node = get_helper(this->m_root, prefix, 0);
    collect(node, prefix, queue);
    return queue;
}

template <typename T, int R>
std::string Trie<T, R>::longest_prefix(std::string key)
{
    int length = search(this->m_root, key, 0, 0);
    return key.substr(0, length);
}
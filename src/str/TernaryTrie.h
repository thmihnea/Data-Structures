#ifndef DS_TERNARY_TRIE_H
#define DS_TERNARY_TRIE_H

#include <string>
#include <optional>
#include <queue>

namespace dsa
{
    template <typename T>
    class Node
    {
    private:
        std::optional<T> m_value;
        char m_c;
        Node<T> *m_left, *m_mid, *m_right;
    
    public:
        Node();

        ~Node();

        Node(T value);

        Node(char c);

        std::optional<T> value();

        Node<T>* left();

        Node<T>* mid();

        Node<T>* right();

        char c();

        void set_c(char c);

        void set_value(T value);

        void set_left(Node<T>* left);

        void set_mid(Node<T>* mid);

        void set_right(Node<T>* right);
    };

    template <typename T>
    class TernaryTrie
    {
    private:
        Node<T>* m_root;
    
    public:
        TernaryTrie();

        ~TernaryTrie();

        void put(std::string key, T value);

        std::optional<T> get(std::string key);

        bool contains(std::string key);
    };
};

#endif
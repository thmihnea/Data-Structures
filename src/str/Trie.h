#ifndef DS_TRIE_H
#define DS_TRIE_H

#include <string>
#include <optional>

namespace dsa
{
    template <typename T, int R>
    class Node
    {
    private:
        static const int r = R;
        std::optional<T> m_value;
        Node<T, R>** m_next;

    public:
        Node(T value);

        Node();

        ~Node();

        std::optional<T> value();

        void set_value(T value);

        Node<T, R>** next();
    };

    template <typename T, int R>
    class Trie
    {
    private:
        static const int r = R;
        Node<T, R>* m_root;
    public:
        Trie();

        ~Trie();

        void put(std::string key, T value);

        std::optional<T> get(std::string key);

        bool contains(std::string key);
    };
}

#endif

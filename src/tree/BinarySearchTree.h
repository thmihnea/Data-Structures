#ifndef DS_BINARY_SEARCH_TREE_H
#define DS_BINARY_SEARCH_TREE_H

#include <type_traits>
#include <optional>

namespace dsa
{
    template <typename T, typename = void>
    struct is_comparable : std::false_type {};

    template <typename T>
    struct is_comparable<T, std::void_t<decltype(std::declval<T>() < std::declval<T>())>> : std::true_type {};

    template <typename T>
    constexpr bool is_comparable_v = is_comparable<T>::value;

    template <typename K, typename V, typename = std::enable_if_t<is_comparable_v<K>>>
    class Node
    {
    private:
        Node<K, V>* left;
        Node<K, V>* right;
        K key;
        V value;

    public:
        Node(const K& key, const V& value);

        ~Node() = default;

        K get_key();

        V get_value();

        Node<K, V>* get_left();

        Node<K, V>* get_right();

        void set_left(Node<K, V>* node);
    
        void set_right(Node<K, V>* right);
    };

    template <typename K, typename V, typename = std::enable_if_t<is_comparable_v<K>>>
    class BinarySearchTree
    {
    private:
        Node<K, V>* root;

    public:
        BinarySearchTree();

        ~BinarySearchTree();

        void put(const K& key, const V& value);

        std::optional<V> get(const K& key);
    };
}

#include "BinarySearchTree.hpp"

#endif
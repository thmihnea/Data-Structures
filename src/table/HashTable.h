#ifndef DS_HASH_TABLE_H
#define DS_HASH_TABLE_H

#include <utility>

namespace dsa
{
    template <typename K, typename V>
    class Node
    {
    private:
        Node<K, V>* m_next;
        K m_key;
        V m_value;

    public:
        Node(const K& key, const V& value);
        Node(K&& key, V&& value);

        const K& GetKey() const;
        const V& GetValue() const;

        void SetValue(const V& value);
        void SetNext(Node<K, V>* next);
        Node<K, V>* GetNext() const;

        ~Node();
    };

    template <typename K, typename V>
    class HashTable
    {
    private:
        Node<K, V>** m_array;
        int m_bucket_size;
        int m_size;
        int m_max_size;
    
    public:
        HashTable();

        ~HashTable();

        int hash(const K key, int size) const;

        void resize();

        int GetSize();

        const V& Get(const K& key);

        void Put(const K& key, const V& value);

        bool Contains(const K& key);
    };
}

#include "HashTable.hpp"

#endif

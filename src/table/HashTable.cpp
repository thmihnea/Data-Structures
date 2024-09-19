#include "HashTable.h"

#include <utility>
#include <memory>
#include <optional>

#define INITIAL_TABLE_SIZE 2

using namespace dsa;

template <typename K, typename V>
Node<K, V>::Node(const K& key, const V& value) : m_key(key), m_value(value)
{
    this->m_next = nullptr;
}

template <typename K, typename V>
Node<K, V>::Node(K&& key, V&& value) : m_key(std::move(key)), m_value(std::move(value))
{
    this->m_next = nullptr;
}

template <typename K, typename V>
Node<K, V>::~Node()
{
    this->m_next = nullptr;
}

template <typename K, typename V>
const K& Node<K, V>::GetKey() const
{
    return this->m_key;
}

template <typename K, typename V>
const V& Node<K, V>::GetValue() const
{
    return this->m_value;
}

template <typename K, typename V>
Node<K, V>* Node<K, V>::GetNext() const
{
    return this->m_next;
}

template <typename K, typename V>
void Node<K, V>::SetNext(Node<K, V>* next)
{
    auto _prev = this->m_next;
    this->m_next = next;
    delete _prev;
}

template <typename K, typename V>
void Node<K, V>::SetValue(const V& value)
{
    this->m_value = value;
}

template <typename K, typename V>
HashTable<K, V>::HashTable() : m_bucket_size(0), m_size(0), m_max_size(INITIAL_TABLE_SIZE)
{
    this->m_array = new Node<K, V>*[this->m_max_size];
    for (int i = 0; i < this->m_max_size; i++)
    {
        this->m_array[i] = nullptr;
    }
}

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
    delete[] this->m_array;
}

template <typename K, typename V>
int HashTable<K, V>::hash(const K key, int size) const
{
    return (std::hash<K>{}(key)) % size;
}

template <typename K, typename V>
int HashTable<K, V>::GetSize()
{
    return this->m_size;
}

template <typename K, typename V>
void HashTable<K, V>::resize()
{
    int needed_size = this->m_max_size;
    if (this->m_bucket_size >= 3 * this->m_max_size / 4)
    {
        needed_size = 2 * needed_size;
    }
    else if (this->m_bucket_size <= this->m_max_size / 4)
    {
        needed_size = needed_size / 2;
    }
    if (needed_size == this->m_max_size) return;

    auto new_array = new Node<K, V>*[needed_size];
    int new_bucket_size = 0;
    for (int i = 0; i < needed_size; i++)
    {
        new_array[i] = nullptr;
    }

    for (int i = 0; i < this->m_max_size; i++)
    {
        Node<K, V>* node = this->m_array[i];
        while (node != nullptr)
        {
            Node<K, V>* next = node->GetNext();
            int new_index = this->hash(node->GetKey(), needed_size);
            node->SetNext(new_array[new_index]);

            if (new_array[new_index] == nullptr)
            {
                new_bucket_size += 1;
            }

            new_array[new_index] = node;
            node = next;
        }
    }

    delete[] this->m_array;
    this->m_array = new_array;
    this->m_max_size = needed_size;
    this->m_bucket_size = new_bucket_size;
}

template <typename K, typename V>
const V& HashTable<K, V>::Get(const K& key)
{
    int index = this->hash(key, this->m_max_size);
    Node<K, V>* current = this->m_array[index];
    while (current != nullptr)
    {
        if (current->GetKey() == key)
        {
            return current->GetValue();
        }
        current = current->GetNext();
    }
    throw std::runtime_error("key not found!");
}

template <typename K, typename V>
void HashTable<K, V>::Put(const K& key, const V& value)
{
    int index = this->hash(key, this->m_max_size);
    Node<K, V>* current = this->m_array[index];
    while (current != nullptr)
    {
        if (current->GetKey() == key)
        {
            current->SetValue(value);
            return;
        }
        current = current->GetNext();
    }

    Node<K, V>* node = new Node<K, V>(key, value);
    if (this->m_array[index] == nullptr)
    {
        this->m_bucket_size += 1;
    }
    node->SetNext(this->m_array[index]);
    this->m_array[index] = node;

    this->resize();
}

template <typename K, typename V>
bool HashTable<K, V>::Contains(const K& key)
{
    return this->Get(key) != std::nullopt;
}

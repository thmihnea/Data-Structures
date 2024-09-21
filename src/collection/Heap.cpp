#include "Heap.h"
#include <optional>

#define INITIAL_HEAP_SIZE 2

using namespace dsa;

template <typename T>
Heap<T>::Heap(int (*compare)(T, T)) : m_size(0), m_max_size(INITIAL_HEAP_SIZE), m_compare(compare)
{
    this->m_heap = new std::optional<T>[INITIAL_HEAP_SIZE];
    for (int i = 0; i < INITIAL_HEAP_SIZE; i++)
    {
        this->m_heap[i] = std::nullopt;
    }
}

template <typename T>
Heap<T>::~Heap()
{
    delete[] this->m_heap;
}

template <typename T>
void Heap<T>::resize()
{
    int max_size = this->m_max_size;
    if (this->m_size >= 3 * this->m_max_size / 4)
    {
        max_size = 2 * this->m_max_size;
    }
    else if (this->m_size <= this->m_max_size / 4)
    {
        max_size = this->m_max_size / 2;
    }
    if (max_size == this->m_max_size) return;

    std::optional<T>* new_array = new std::optional<T>[max_size];
    for (int i = 0; i < this->m_size; i++)
    {
        new_array[i] = this->m_heap[i];
    }
    for (int i = this->m_size; i < max_size; i++)
    {
        new_array[i] = std::nullopt;
    }

    delete[] this->m_heap;
    this->m_heap = new_array;
    this->m_max_size = max_size;
}

template <typename T>
void Heap<T>::swap(int i, int j)
{
    std::optional<T> aux = this->m_heap[i];
    this->m_heap[i] = this->m_heap[j];
    this->m_heap[j] = aux;
}

template <typename T>
void Heap<T>::sink(int node)
{
    while (2 * node + 1 < this->m_size)
    {
        int left_child = 2 * node + 1;
        int right_child = left_child + 1;
        int larger_child = left_child;

        if (
            right_child < this->m_size && 
            this->m_heap[right_child] && 
            this->m_heap[left_child] &&
            this->m_compare(*this->m_heap[right_child], *this->m_heap[left_child]) == -1
        ) larger_child = right_child;

        if (!this->m_heap[node] || !this->m_heap[larger_child] || this->m_compare(*this->m_heap[node], *this->m_heap[larger_child]) != 1)
        {
            break;
        }

        this->swap(node, larger_child);
        node = larger_child;
    }
}

template <typename T>
void Heap<T>::swim(int node)
{
    while (node > 0)
    {
        int parent = (node - 1) / 2;
        if (!this->m_heap[node] || !this->m_heap[parent] || this->m_compare(*this->m_heap[node], *this->m_heap[parent]) != -1)
        {
            break;
        }
        this->swap(node, parent);
        node = parent;
    }
}

template <typename T>
void Heap<T>::push(const T& element)
{
    this->m_heap[this->m_size++] = element;
    this->swim(this->m_size - 1);
    this->resize();
}

template <typename T>
T Heap<T>::pop()
{
    T element = *this->m_heap[0];
    this->swap(0, this->m_size - 1);
    this->m_heap[--this->m_size] = std::nullopt;
    this->sink(0);
    this->resize();
    return element;
}
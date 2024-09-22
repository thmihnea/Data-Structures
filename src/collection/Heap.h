#ifndef DS_HEAP_H
#define DS_HEAP_H

#include <optional>

namespace dsa
{
    template <typename T>
    class Heap
    {
    private:
        int (*m_compare)(T, T);
        std::optional<T>* m_heap;
        int m_size;
        int m_max_size;

    public:
        Heap(int (*compare)(T, T));

        ~Heap();

        void resize();

        void sink(int node);

        void swim(int node);

        void swap(int i, int j);

        void push(const T& element);

        int size();

        bool empty();

        T pop();
};
}

#include "Heap.hpp"

#endif
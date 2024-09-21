#include "Stack.h"
#include <iostream>

#define INITIAL_STACK_SIZE 2

using namespace dsa;

template <typename T>
Stack<T>::Stack() : m_size(0), m_max_size(INITIAL_STACK_SIZE)
{
    this->m_stack = new T[2];
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] this->m_stack;
}

template <typename T>
void Stack<T>::resize()
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

    T* new_array = new T[max_size];
    for (int i = 0; i < this->m_size; i++)
    {
        new_array[i] = this->m_stack[i];
    }

    delete[] this->m_stack;
    this->m_stack = new_array;
    this->m_max_size = max_size;
}

template <typename T>
int Stack<T>::size()
{
    return this->m_size;
}

template <typename T>
bool Stack<T>::empty()
{
    return this->m_size == 0;
}

template <typename T>
void Stack<T>::push(const T& element)
{
    this->m_stack[this->m_size++] = element;
    this->resize();
}

template <typename T>
T Stack<T>::pop()
{
    T element = this->m_stack[--this->m_size];
    this->resize();
    return element;
}


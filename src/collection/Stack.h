#ifndef DS_STACK_H
#define DS_STACK_H

namespace dsa
{
    template <typename T>
    class Stack
    {
    private:
        T* m_stack;
        int m_size;
        int m_max_size;
    public:
        Stack();

        ~Stack();

        void resize();

        int size();

        bool empty();

        void push(const T& element);

        T pop();
};
}

#endif
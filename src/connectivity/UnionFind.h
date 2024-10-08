#ifndef DS_UNION_FIND_H
#define DS_UNION_FIND_H

namespace dsa
{
    class UnionFind
    {
    private:
        int* m_parent;
        int* m_size;
        int m_capacity;

    public:
        UnionFind(int capacity);

        ~UnionFind();

        int GetRoot(int p);
        int GetSize(int p);
        bool Connected(int p, int q);
        void Union(int p, int q);
    };
}


#endif

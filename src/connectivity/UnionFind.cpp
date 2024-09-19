#include "UnionFind.h"

using namespace dsa;

UnionFind::UnionFind(int capacity) : m_capacity(capacity)
{
    this->m_parent = new int[capacity];
    this->m_size = new int[capacity];
    for (int i = 0; i < capacity; i++)
    {
        this->m_parent[i] = i;
        this->m_size[i] = 1;
    }
}

UnionFind::~UnionFind()
{
    delete[] this->m_parent;
    delete[] this->m_size;
}

int UnionFind::GetRoot(int p)
{
    while (p != this->m_parent[p])
    {
        // Flatten the parent tree when going up
        // the chain.
        this->m_parent[p] = this->m_parent[this->m_parent[p]];
        p = this->m_parent[p];
    }
    return p;
}

int UnionFind::GetSize(int p)
{
    return this->m_size[p];
}

bool UnionFind::Connected(int p, int q)
{
    return this->GetRoot(p) == this->GetRoot(q);
}

void UnionFind::Union(int p, int q)
{
    int root_p = this->GetRoot(p);
    int root_q = this->GetRoot(q);
    if (root_p == root_q)
    {
        return;
    }
    // We append smaller tree to larger tree in
    // order to prevent massive trees from emerging.
    // Note that we must attempt to keep our structure
    // O(log n).
    if (this->m_size[root_p] > this->m_size[root_q])
    {
        this->m_parent[root_q] = root_p;
        this->m_size[root_p] += this->m_size[root_q];
    }
    else
    {
        this->m_parent[root_p] = root_q;
        this->m_size[root_q] += this->m_size[root_p];
    }
}
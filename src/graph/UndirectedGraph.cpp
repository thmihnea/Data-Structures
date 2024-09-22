#include "UndirectedGraph.h"
#include <vector>
#include <stack>
#include <queue>

using namespace dsa;

UndirectedGraph::UndirectedGraph(int size) : m_size(size)
{
    this->m_adj = std::vector<std::vector<int>>(size);
    this->m_degree = std::vector<int>(size, 0);
}

void UndirectedGraph::add_edge(int v, int w)
{
    this->m_adj[v].push_back(w);
    this->m_adj[w].push_back(v);
    this->m_degree[v] += 1;
    this->m_degree[w] += 1;
}

std::vector<int> UndirectedGraph::adj(int v)
{
    return this->m_adj[v];
}

int UndirectedGraph::degree(int v)
{
    return this->m_degree[v];
}

int UndirectedGraph::get_size()
{
    return this->m_size;
}

Path::Path(int source, UndirectedGraph& graph) : m_source(source), m_graph(graph)
{
    this->m_edge_to = std::vector<int>(graph.get_size());
    this->m_visited = std::vector<bool>(graph.get_size(), false);
    
    for (int i = 0; i < graph.get_size(); i++)
    {
        this->m_edge_to[i] = i;
    }
}

void Path::dfs(int v)
{
    this->m_visited[v] = true;
    for (auto &edge : this->m_graph.adj(v))
    {
        if (!this->m_visited[edge])
        {
            this->m_edge_to[edge] = v;
            this->dfs(edge);
        }
    }
}

bool Path::has_path_to(int v)
{
    while (v != this->m_edge_to[v])
    {
        v = this->m_edge_to[v];
    }
    return v == this->m_source;
}

std::vector<int> Path::get_path_to(int v)
{
    if (!this->has_path_to(v)) return std::vector<int>();
    std::stack<int> path;
    while (v != this->m_edge_to[v])
    {
        path.push(v);
        v = this->m_edge_to[v];
    }
    path.push(this->m_source);
    std::vector<int> result;
    while (!path.empty())
    {
        int front = path.top();
        result.push_back(front);
        path.pop();
    }
    return result;
}

void Path::bfs(int v)
{
    std::queue<int> q;
    q.push(v);
    this->m_visited[v] = true;
    while (!q.empty())
    {
        int front = q.front();
        q.pop();
        for (auto &edge : this->m_graph.adj(front))
        {
            if (!this->m_visited[edge])
            {
                q.push(edge);
                this->m_edge_to[edge] = front;
                this->m_visited[edge] = true;
            }
        }
    }
}

Components::Components(UndirectedGraph& graph) : m_graph(graph), m_count(0)
{
    this->m_marks = std::vector<int>(graph.get_size(), 0);
}

void Components::dfs(int v)
{
    this->m_marks[v] = this->m_count;
    for (auto &edge : this->m_graph.adj(v))
    {
        if (!this->m_marks[edge])
        {
            this->dfs(edge);
        }
    }
}

void Components::mark()
{
    for (int i = 0; i < this->m_graph.get_size(); i++)
    {
        if (!this->m_marks[i])
        {
            this->m_count++;
            this->dfs(i);
        }
    }
}

int Components::get_components()
{
    return this->m_count;
}
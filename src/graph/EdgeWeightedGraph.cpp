#include "EdgeWeightedGraph.h"
#include <vector>
#include <queue>
#include "../collection/Heap.h"
#include "../connectivity/UnionFind.h"
#include <iostream>

using namespace dsa;

static int compare(Edge a, Edge b)
{
    if (a.get_weight() < b.get_weight()) return -1;
    else if (a.get_weight() > b.get_weight()) return 1;
    else return 0;
}

Edge::Edge(int v, int w, double weight) : m_v(v), m_w(w), m_weight(weight) {}

int Edge::either()
{
    return this->m_v;
}

int Edge::other(int v)
{
    return v == this->m_v ? this->m_w : this->m_v;
}

double Edge::get_weight()
{
    return this->m_weight;
}

EdgeWeightedGraph::EdgeWeightedGraph(int size) : m_adj(std::vector<std::vector<Edge>>(size)), m_edges(std::vector<Edge>()) {}

void EdgeWeightedGraph::add_edge(Edge& edge)
{
    int v = edge.either();
    int w = edge.other(v);
    this->m_adj[v].push_back(edge);
    this->m_adj[w].push_back(edge);
    this->m_edges.push_back(edge);
}

std::vector<Edge> EdgeWeightedGraph::edges()
{
    return this->m_edges;
}

std::vector<Edge> EdgeWeightedGraph::adj(int v)
{
    return this->m_adj[v];
}

int EdgeWeightedGraph::size()
{
    return this->m_adj.size();
}

MinimumSpanningTree::MinimumSpanningTree(EdgeWeightedGraph& graph) : m_graph(graph) {}

std::queue<Edge> MinimumSpanningTree::kruskal()
{
    std::queue<Edge> tree;
    Heap<Edge> heap(&compare);
    for (auto &edge : this->m_graph.edges())
    {
        heap.push(edge);
    }

    UnionFind uf(this->m_graph.size());
    while (!heap.empty() && tree.size() < this->m_graph.size() - 1)
    {
        auto edge = heap.pop();
        int v = edge.either();
        int w = edge.other(v);
        if (!uf.Connected(v, w))
        {
            uf.Union(v, w);
            tree.push(edge);
        }
    }
    return tree;
}

static void visit(EdgeWeightedGraph& graph, std::vector<bool>& visited, dsa::Heap<Edge>& heap, int v)
{
    visited[v] = true;
    for (auto& edge : graph.adj(v))
    {
        if (!visited[edge.other(v)])
        {
            heap.push(edge);
        }
    }
}

std::queue<Edge> MinimumSpanningTree::prim()
{
    std::queue<Edge> tree;
    Heap<Edge> heap(&compare);
    std::vector<bool> visited(this->m_graph.size());
    visit(this->m_graph, visited, heap, 0);

    while (!heap.empty())
    {
        auto edge = heap.pop();
        int v = edge.either();
        int w = edge.other(v);
        if (visited[v] && visited[w]) continue;
        tree.push(edge);
        if (!visited[v]) visit(this->m_graph, visited, heap, v);
        if (!visited[w]) visit(this->m_graph, visited, heap, w);
    }
}
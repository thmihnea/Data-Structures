#include "EdgeWeightedDigraph.h"
#include <vector>
#include <string>
#include <limits>
#include "../collection/Heap.h"

using namespace dsa;

DirectedEdge::DirectedEdge(int v, int w, double weight) : m_v(v), m_w(w), m_weight(weight) {}

int DirectedEdge::from()
{
    return this->m_v;
}

int DirectedEdge::to()
{
    return this->m_w;
}

double DirectedEdge::weight()
{
    return this->m_weight;
}

std::string DirectedEdge::to_string()
{
    return "Edge: " + std::to_string(this->from()) + " -> " + std::to_string(this->to()) + ", Weight: " + std::to_string(this->weight());
}

EdgeWeightedDigraph::EdgeWeightedDigraph(int size) : m_edges(std::vector<DirectedEdge>()), m_adj(std::vector<std::vector<DirectedEdge>>(size)) {}

int EdgeWeightedDigraph::v_size()
{
    return this->m_adj.size();
}

int EdgeWeightedDigraph::e_size()
{
    return this->m_edges.size();
}

std::vector<DirectedEdge> EdgeWeightedDigraph::edges()
{
    return this->m_edges;
}

std::vector<DirectedEdge> EdgeWeightedDigraph::adj(int v)
{
    return this->m_adj[v];
}

void EdgeWeightedDigraph::add_edge(DirectedEdge& edge)
{
    this->m_edges.push_back(edge);
    int v = edge.from();
    this->m_adj[v].push_back(edge);
}

ShortestPath::ShortestPath(EdgeWeightedDigraph& graph, int source) : m_graph(graph), m_source(source)
{
    this->m_edge_to = std::vector<DirectedEdge>(graph.v_size());
    this->m_dist_to = std::vector<double>(graph.v_size(), std::numeric_limits<double>::infinity());

    this->m_dist_to[source] = 0;
}

void ShortestPath::relax(DirectedEdge& edge)
{
    int v = edge.from(), w = edge.to();
    if (this->m_dist_to[w] > this->m_dist_to[v] + edge.weight())
    {
        this->m_dist_to[w] = this->m_dist_to[v] + edge.weight();
        this->m_edge_to[w] = edge;
    }
}

static int compare(std::pair<int, double> a, std::pair<int, double> b)
{
    if (a.second < b.second) return -1;
    else if (a.second > b.second) return 1;
    else return 0;
}

void ShortestPath::dijkstra()
{
    Heap<std::pair<int, double>> heap(&compare);

    heap.push({this->m_source, 0.0});

    while (!heap.empty())
    {
        auto [v, dist] = heap.pop();

        if (dist > this->m_dist_to[v])
            continue; 

        for (auto& e : this->m_graph.adj(v))
        {
            this->relax(e);
            int w = e.to();
            if (this->m_dist_to[w] == this->m_dist_to[v] + e.weight())
            {
                heap.push({w, this->m_dist_to[w]});
            }
        }
    }
}

void ShortestPath::bellman_ford()
{
    for (int i = 0; i < this->m_graph.v_size(); i++)
    {
        for (int v = 0; v < this->m_graph.v_size(); v++)
        {
            for (auto &edge : this->m_graph.adj(v))
            {
                this->relax(edge);
            }
        }
    }
}

double ShortestPath::distance_to(int v)
{
    return this->m_dist_to[v];
}

#include "FlowNetwork.h"
#include <queue>
#include <limits>

using namespace dsa;

FlowEdge::FlowEdge(int v, int w, double capacity) : m_v(v), m_w(w), m_capacity(capacity), m_flow(0) {}

int FlowEdge::from()
{
    return this->m_v;
}

int FlowEdge::to()
{
    return this->m_w;
}

double FlowEdge::capacity()
{
    return this->m_capacity;
}

double FlowEdge::flow()
{
    return this->m_flow;
}

int FlowEdge::other(int v)
{
    if (v == this->m_v) return this->m_w;
    else return this->m_w;
}

double FlowEdge::residual_capacity(int v)
{
    if (v == this->m_v) return this->m_flow;
    else return this->m_capacity - this->m_flow;
}

void FlowEdge::add_flow(int v, double delta)
{
    if (v == this->m_v) this->m_flow += delta;
    else this->m_flow -= delta;
}

FlowNetwork::FlowNetwork(int size) : m_edges(std::vector<FlowEdge>()), m_adj(std::vector<std::vector<FlowEdge>>(size)) {}

int FlowNetwork::v_size()
{
    return this->m_adj.size();
}

int FlowNetwork::e_size()
{
    return this->m_edges.size();
}

std::vector<FlowEdge> FlowNetwork::edges()
{
    return this->m_edges;
}

std::vector<FlowEdge> FlowNetwork::adj(int v)
{
    return this->m_adj[v];
}

void FlowNetwork::add_edge(FlowEdge& edge)
{
    int v = edge.from(), w = edge.to();
    this->m_adj[v].push_back(edge);
    this->m_adj[w].push_back(edge);
}

MincutMaxflow::MincutMaxflow(FlowNetwork& network, int s, int t) : m_network(network), m_s(s), m_t(t), m_value(0)
{
    this->m_marked = std::vector<bool>(network.v_size());
    this->m_edge_to = std::vector<FlowEdge>(network.v_size());
}

double MincutMaxflow::value()
{
    return this->m_value;
}

bool MincutMaxflow::in_cut(int v)
{
    return this->m_marked[v];
}

bool MincutMaxflow::has_path()
{
    this->m_marked.clear();
    this->m_edge_to.clear();

    std::queue<int> q;
    q.push(this->m_s);
    this->m_marked[this->m_s] = true;

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        for (auto &edge : this->m_network.adj(v))
        {
            int w = edge.other(v);
            if (edge.residual_capacity(w) > 0 && !this->m_marked[w])
            {
                this->m_edge_to[w] = edge;
                this->m_marked[w] = true;
                q.push(w);
            }
        }
    }

    return this->m_marked[this->m_t];
}

void MincutMaxflow::ford_fulkerson()
{
    while (this->has_path())
    {
        double current = std::numeric_limits<double>::infinity();
        for (int v = this->m_t; v != this->m_s; v = this->m_edge_to[v].other(v))
        {
            current = std::min(current, this->m_edge_to[v].residual_capacity(v));
        }

        for (int v = this->m_t; v != this->m_s; v = this->m_edge_to[v].other(v))
        {
            this->m_edge_to[v].add_flow(v, current);
        }

        this->m_value += current;
    }
}
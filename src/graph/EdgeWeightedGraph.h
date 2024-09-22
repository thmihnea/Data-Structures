#ifndef DS_EDGE_WEIGHTED_GRAPH_H
#define DS_EDGE_WEIGHTED_GRAPH_H

#include <vector>
#include <queue>

namespace dsa
{
    class Edge
    {
    private:
        int m_v;
        int m_w;
        double m_weight;

    public:
        Edge(int v, int w, double weight);

        ~Edge() = default;

        int either();

        int other(int v);

        double get_weight();
    };

    class EdgeWeightedGraph
    {
    private:
        std::vector<std::vector<Edge>> m_adj;
        std::vector<Edge> m_edges;
    
    public:
        EdgeWeightedGraph(int size);

        ~EdgeWeightedGraph() = default;

        void add_edge(Edge& edge);

        std::vector<Edge> adj(int v);

        std::vector<Edge> edges();

        int size();
    };

    class MinimumSpanningTree
    {
    private:
        EdgeWeightedGraph& m_graph;
    
    public:
        MinimumSpanningTree(EdgeWeightedGraph& graph);

        ~MinimumSpanningTree() = default;

        std::queue<Edge> kruskal();

        std::queue<Edge> prim();
    };
};

#endif
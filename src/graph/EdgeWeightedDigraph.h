#ifndef DS_EDGE_WEIGHTED_DIGRAPH_H
#define DS_EDGE_WEIGHTED_DIGRAPH_H

#include <vector>
#include <string>

namespace dsa
{
    class DirectedEdge
    {
    private:
        int m_v;
        int m_w;
        double m_weight;
    
    public:
        DirectedEdge() = default;

        DirectedEdge(int v, int w, double weight);

        ~DirectedEdge() = default;

        int from();

        int to();

        double weight();

        std::string to_string();
    };

    class EdgeWeightedDigraph
    {
    private:
        std::vector<DirectedEdge> m_edges;
        std::vector<std::vector<DirectedEdge>> m_adj;
    
    public:
        EdgeWeightedDigraph(int size);

        ~EdgeWeightedDigraph() = default;

        int v_size();

        int e_size();

        std::vector<DirectedEdge> edges();

        std::vector<DirectedEdge> adj(int v);

        void add_edge(DirectedEdge& edge);
    };

    class ShortestPath
    {
    private:
        EdgeWeightedDigraph& m_graph;
        int m_source;
        std::vector<DirectedEdge> m_edge_to;
        std::vector<double> m_dist_to;

    public:
        ShortestPath(EdgeWeightedDigraph& graph, int source);

        ~ShortestPath() = default;

        void relax(DirectedEdge& edge);

        void dijkstra();

        void bellman_ford();

        double distance_to(int v);
    };
};

#endif
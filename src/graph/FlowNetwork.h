#ifndef DS_FLOW_NETWORK_H
#define DS_FLOW_NETWORK_H

#include <vector>

namespace dsa
{
    class FlowEdge
    {
    private:
        int m_v;
        int m_w;
        double m_capacity;
        double m_flow;
    
    public:
        FlowEdge(int v, int w, double capacity);

        ~FlowEdge() = default;

        int from();

        int to();

        int other(int v);

        double capacity();

        double flow();

        double residual_capacity(int v);

        void add_flow(int v, double delta);
    };

    class FlowNetwork
    {
    private:
        std::vector<FlowEdge> m_edges;
        std::vector<std::vector<FlowEdge>> m_adj;
    public:
        FlowNetwork(int size);

        ~FlowNetwork() = default;

        int v_size();

        int e_size();
        
        std::vector<FlowEdge> edges();

        std::vector<FlowEdge> adj(int v);

        void add_edge(FlowEdge& edge);
    };

    class MincutMaxflow
    {
    private:
        FlowNetwork& m_network;
        std::vector<bool> m_marked;
        std::vector<FlowEdge> m_edge_to;
        double m_value;
        int m_s;
        int m_t;
    
    public:
        MincutMaxflow(FlowNetwork& network, int s, int t);

        ~MincutMaxflow() = default;

        bool has_path();

        double value();

        bool in_cut(int v);

        void ford_fulkerson();
    };
};

#endif
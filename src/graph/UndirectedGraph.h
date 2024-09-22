#ifndef DS_UNDIRECTED_GRAPH_H
#define DS_UNDIRECTED_GRAPH_H

#include <vector>

namespace dsa
{
    class UndirectedGraph
    {
    private:
        std::vector<std::vector<int>> m_adj;
        std::vector<int> m_degree;
        int m_size;

    public:
        UndirectedGraph(int size);

        ~UndirectedGraph() = default;

        void add_edge(int v, int w);

        std::vector<int> adj(int v);

        int degree(int v);

        int get_size();
    };

    class Path
    {
    private:
        UndirectedGraph& m_graph;
        int m_source;
        std::vector<int> m_edge_to;
        std::vector<bool> m_visited;
    
    public:
        Path(int source, UndirectedGraph& graph);

        ~Path() = default;

        bool has_path_to(int v);

        std::vector<int> get_path_to(int v);

        void dfs(int v);

        void bfs(int v);
    };

    class Components
    {
    private:
        UndirectedGraph& m_graph;
        std::vector<int> m_marks;
        int m_count;
    public:
        Components(UndirectedGraph& graph);

        ~Components() = default;

        void dfs(int v);

        void mark();

        int get_components();
    };
};

#endif
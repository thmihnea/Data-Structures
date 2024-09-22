set(SOURCES
    collection/Heap.hpp
    collection/Stack.hpp
    connectivity/UnionFind.cpp
    table/HashTable.hpp
    tree/BinarySearchTree.hpp
    sort/Sort.cpp
    graph/UndirectedGraph.cpp
    graph/EdgeWeightedGraph.cpp
)

add_executable(data-structures ${SOURCES})
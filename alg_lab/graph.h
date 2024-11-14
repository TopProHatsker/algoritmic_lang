#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <stack>


class Graph
{
    // матрица смежности (adjacency matrix)
    std::vector<std::vector<uint>> adjMtr;

public:

    Graph() = default;

    void loadMatrix(const std::vector<std::vector<uint>>& mtr);

    void topologicalSortUtil(
        int v,
        const std::vector<std::vector<uint>>& adjMatrix,
        std::vector<bool>& visited,
        std::stack<uint>& Stack);

    std::stack<uint> topologicalSort(
        const std::vector<std::vector<uint>>& adjMatrix);

    void printMatrix(std::ostream& os) const;
    void printTopolog(std::ostream& os);

};


#endif // GRAPH_H

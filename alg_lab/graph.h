#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <stack>


class Graph
{
    // матрица смежности (adjacency matrix)
    std::vector<std::vector<uint>> adjMtr;

    // матрица производительности
    std::vector<std::vector<float>> effMtr;

public:

    Graph() = default;

    void loadMatrix(const std::vector<std::vector<uint>>& mtr);
    void loadEffMatrix(const std::vector<std::vector<float>>& mtr);

    void topologicalSortUtil(
        int v,
        const std::vector<std::vector<uint>>& adjMatrix,
        std::vector<bool>& visited,
        std::stack<uint>& Stack);

    std::stack<uint> topologicalSort(
        const std::vector<std::vector<uint>>& adjMatrix);

    void printMatrix(std::ostream& os) const;
    void printEffMatrix(std::ostream &os) const;

    void printTopolog(std::ostream& os);

    std::vector<uint> dijkstra(
        const std::vector<std::vector<uint>>& mtr,
        uint start,
        uint end
    );

    void printShortestPath(std::ostream& os, std::istream& is);
    void printMaxFlow(std::ostream& os, std::istream& is);

};


#endif // GRAPH_H

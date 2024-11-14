#include "graph.h"


#include <iostream>
#include <vector>
using namespace std;


void Graph::loadMatrix(const std::vector<std::vector<uint>>& mtr) {
    this->adjMtr = mtr;
}


void Graph::topologicalSortUtil(
    int v,
    const std::vector<std::vector<uint>>& adjMatrix,
    std::vector<bool>& visited,
    std::stack<uint>& Stack
) {

    visited[v] = true;

    // Рекурсивно посещаем все вершины, смежные с текущей
    for (int i = 0; i < adjMatrix.size(); ++i) {
        if (adjMatrix[v][i] && !visited[i]) {
            topologicalSortUtil(i, adjMatrix, visited, Stack);
        }
    }

    // Добавляем текущую вершину в стек
    Stack.push(v);
}

std::stack<uint> Graph::topologicalSort(const std::vector<std::vector<uint>>& adjMatrix) {
    std::stack<uint> id_stack;
    std::vector<bool> visited(adjMatrix.size(), false);

    // Вызываем рекурсивную функцию для всех вершин графа
    for (int i = 0; i < adjMatrix.size(); ++i) {
        if (!visited[i]) {
            topologicalSortUtil(i, adjMatrix, visited, id_stack);
        }
    }

    return id_stack;
    // Печатаем элементы топологической сортировки
    // while (!Stack.empty()) {
    //     std::cout << Stack.top() + 1 << " ";
    //     Stack.pop();
    // }
}


void Graph::printTopolog(std::ostream& os) {
    // this->adjMtr = {
    //     {0, 0, 0, 1, 0},
    //     {0, 0, 0, 0, 1},
    //     {0, 1, 0, 0, 0},
    //     {0, 0, 1, 0, 0},
    //     {0, 0, 0, 1, 0}
    // };

    if (this->adjMtr.empty()) {
        os << "> Empty" << std::endl;
        return;
    }
    os << "\n\nТопологическая сортировка графа:\n\n";
    std::stack<uint> sorted_id = this->topologicalSort(this->adjMtr);

    for (uint i = 0; !sorted_id.empty(); i++) {
        os
            << "  "
            << (i % 2 ? "/" : "\\")
            << "^"
            << (i % 2 ? "/" : "\\")
            << "  "
            << sorted_id.top() + 1
            << "\n";

        sorted_id.pop();
    }
}


void Graph::printMatrix(std::ostream& os) const {
    os << "Матрица смежности:\n\n";
    if (this->adjMtr.empty()) {
        os << "> Empty" << std::endl;
        return;
    }

    os << "   ";
    for (uint i = 1; i <= this->adjMtr.size(); i++) {
        //os << i << "   ";
        printf("%4d|", i);
    }
    os << "\n  г";

    for (uint i = 0; i < this->adjMtr.size(); i++) {
        printf("----+");
    }
    os << std::endl;

    for (uint i = 0; i < this->adjMtr.size(); i++) {
        os << " " << i + 1 << "|";
        for (uint j = 0; j < this->adjMtr.size(); j++) {
            if (adjMtr[i][j])
                printf("%4d|", adjMtr[i][j]);
            else
                printf("  - |");
        }
        os << std::endl;
    }

}

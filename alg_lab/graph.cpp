#include "graph.h"
#include "func.h"

//#include <queue>
#include <limits>
#include <algorithm>
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
            << "v"
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


// - - - - - - - - - - - - Dijkstra - - - - - - - - - - - - -

#define MAX_UINT numeric_limits<uint>::max()

vector<uint> Graph::dijkstra(const vector<vector<uint>>& mtr, uint start, uint end) {
    size_t n = mtr.size();
    vector<uint> dist(n, MAX_UINT); // Вектор расстояний
    vector<uint> prev(n, MAX_UINT); // Вектор предков
    vector<bool> visited(n, false); // Вектор посещённых вершин

    dist[start] = 0; // Расстояние до начальной вершины равно 0

    for (size_t i = 0; i < n; ++i) {
        // Находим вершину с минимальным расстоянием
        uint minDist = MAX_UINT;
        int currentVertex = -1;

        for (size_t j = 0; j < n; ++j) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                currentVertex = j;
            }
        }

        if (currentVertex == -1) {
            break; // Все доступные вершины посещены
        }

        visited[currentVertex] = true;

        // Обновляем расстояния до соседей
        for (size_t neighbor = 0; neighbor < n; neighbor++) {
            if (mtr[currentVertex][neighbor] > 0 && !visited[neighbor]) {    // Если есть ребро и сосед не посещён
                uint newDist = dist[currentVertex] + mtr[currentVertex][neighbor];
                if (newDist < dist[neighbor]) {                 // Если найдено более короткое расстояние
                    dist[neighbor] = newDist;
                    prev[neighbor] = currentVertex;
                }
            }
        }
    }

    // Восстановление пути
    vector<uint> path;
    for (uint at = end; at != MAX_UINT; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    // Если путь не найден, возвращаем пустой вектор
    if (path.size() == 1 && path[0] != start) {
        return {};
    }

    return path;
}


void Graph::printShortestPath(ostream& os, istream& is) {
    os << "> Enter src station id: ";
    uint src_id = check_input(1UL, this->adjMtr.size()) - 1;

    os << "> Enter dest station id: ";
    uint dest_id = check_input(1UL, this->adjMtr.size()) - 1;

    vector<uint> shortestPath = dijkstra(this->adjMtr, src_id, dest_id);


    if (shortestPath.empty()) {
        os << "\n> Путь не найден"<< endl;
    } else {
        os  << "\n> Кратчайший путь от "
           << src_id + 1
           << " до "
           << dest_id + 1
           << ": ";

        uint curr = shortestPath[0], prev = 0, sum = 0;
        for (uint vertex : shortestPath) {
            prev = curr;
            curr = vertex;
            os << vertex + 1 << " ";
            sum += this->adjMtr[prev][curr];
        }
        os << endl;

        os << "  Длина: " << sum << endl;
    }

    is.ignore();
}


// - - - - - - - - - - - - MAX Flow - - - - - - - - - - - - -

void Graph::loadEffMatrix(const std::vector<std::vector<float>>& mtr) {
    this->effMtr = mtr;
}


void Graph::printEffMatrix(std::ostream &os) const {
    os << "Матрица эффективности:\n\n";
    if (this->effMtr.empty()) {
        os << "> Empty" << std::endl;
        return;
    }

    os << "   ";
    for (uint i = 1; i <= this->effMtr.size(); i++) {
        // os << i << "   ";
        printf("%4d|", i);
    }
    os << "\n  г";

    for (uint i = 0; i < this->effMtr.size(); i++) {
        printf("----+");
    }
    os << std::endl;

    for (uint i = 0; i < this->effMtr.size(); i++) {
        os << " " << i + 1 << "|";
        for (uint j = 0; j < this->effMtr.size(); j++) {
            if (effMtr[i][j]) {
                printf("%2.2f|", effMtr[i][j]);
            } else
                printf("  - |");
        }
        os << std::endl;
    }
}


// TODO: add logic
void Graph::printMaxFlow(std::ostream& os, std::istream& is) {
    os << "\n<max flow func>" << endl;
}

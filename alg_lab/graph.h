#ifndef GRAPH_H
#define GRAPH_H


#include <iostream>
#include <vector>
#include <set>

#include "station.h"
#include <unordered_map>


// Структура данных для хранения ребра Graph
struct Edge {
    uint st_src, pipe, st_dest;
};

std::istream& operator>>(std::istream& is, Edge& edge);


// Класс для представления graphического объекта
class Graph
{

    uint size = 0;

public:

    // вектор ребер
    std::vector<Edge> edges;

    // вектор векторов для представления списка смежности
    std::vector<std::vector<int>> adjList;

    // Конструктор Graphа
    Graph() = default;

    Graph(uint new_size) : Graph() {
        this->size = new_size;
    }


    void addEdge(Edge const &edge) {
        edges.push_back(edge);
        this->autoSize();
        this->gen();
    }

    void gen() {
        for(auto t: adjList)
            t.clear();
        adjList.clear();

        // изменить размер вектора, чтобы он содержал `n` элементов типа `vector<int>`
        adjList.resize(size);

        // добавляем ребра в ориентированный graph
        for (auto &edge: edges) {
            adjList[edge.st_src].push_back(edge.st_dest);
        }
    }

    void print() const {        
        std::cout << "adjList:\n\n";
        uint row = 0;
        for (auto t1: adjList) {
            std::cout << " " << row << " ->";
            for (auto t2: t1) {
                std::cout << ' ' << t2;
            }
            row++;
            std::cout << "\n";
        }
        std::cout << std::endl;
    }

    void setSize(uint new_size) {
        this->size = new_size;
    }

    void autoSize() {
        std::set<uint> uniq;

        for (auto t: edges) {
            uniq.insert(t.st_dest);
            uniq.insert(t.st_src);
        }

        this->setSize(uniq.size());
    }

    uint getSize() const {
        return size;
    }
};



int graph_main();

void addEdge(Graph& graph);
void printGraph(Graph& graph, unordered_map<uint, Station> stations);

#endif // GRAPH_H

#include "graph.h"


#include <iostream>
#include <vector>
using namespace std;


std::istream& operator>>(std::istream& is, Edge& edge) {
    std::cout << " Source CS id: ";
    is >> edge.st_src;

    std::cout << " Destination CS id: ";
    is >> edge.st_dest;

    std::cout << " Pipe id: ";   // FIXME
    is >> edge.pipe;

    is.ignore();
    return is;
}




// Выполняем поиск в глубину на Graphе и устанавливаем время отправления всех
// вершины Graph
void DFS(
    Graph const &graph,
    int v,
    vector<bool> &discovered,
    vector<int> &departure,
    int &time
){

    // помечаем текущий узел как обнаруженный
    discovered[v] = true;

    // устанавливаем время прибытия вершины `v`
    time++;

    // делаем для каждого ребра (v, u)
    for (int u: graph.adjList[v])
    {
        // если `u` еще не обнаружен
        if (!discovered[u]) {
            DFS(graph, u, discovered, departure, time);
        }
    }

    // готов к возврату
    // устанавливаем время отправления вершины `v`
    departure[time] = v;
    time++;
}

// Функция для выполнения топологической сортировки заданной DAG
vector<uint> doTopologicalSort(Graph const &graph) {

    uint n = graph.getSize();

    // departure[] сохраняет номер вершины, используя время отправления в качестве индекса
    vector<int> departure(2*n, -1);

    /* Если бы мы сделали наоборот, т.е. заполнили бы массив
       со временем отправления, используя номер вершины в качестве индекса, мы бы
       нужно отсортировать позже */

    // чтобы отслеживать, открыта вершина или нет
    vector<bool> discovered(n);
    int time = 0;

    // выполняем поиск в глубину на всех неоткрытых вершинах
    for (uint i = 0; i < n; i++)
    {
        if (!discovered[i]) {
            DFS(graph, i, discovered, departure, time);
        }
    }

    vector<uint> dep_arr;
    // Печатаем вершины в порядке их убывания
    // время отправления в DFS, т.е. в топологическом порядке
    for (int i = 2*n - 1; i >= 0; i--)
    {
        if (departure[i] != -1) {
            //cout << departure[i] << " ";
            dep_arr.push_back(departure[i]);
        }
    }

    return dep_arr;
}


int graph_main()
{
    // vector ребер Graph согласно схеме выше
    vector<Edge> edges =
        {
            {0, 1, 6},
            {1, 2, 2},
            {1, 3, 4},
            {1, 4, 6},
            {3, 5, 0},
            {3, 6, 4},
            {5, 7, 1},
            {7, 8, 0},
            {7, 9, 1}
        };

    // строим graph из заданных ребер
    Graph graph;         // Указываем число вершин

    for (auto t: edges)
        graph.addEdge(t);

    graph.gen();
    graph.print();

    // выполняем топологическую сортировку
    cout << "Topolog sort: ";
    doTopologicalSort(graph);
    cout << endl;

    return 0;
}


void addEdge(Graph &graph) {
    cout << "> New Edge:\n";

    Edge new_edge;
    cin >> new_edge;

    graph.addEdge(new_edge);

}

void printGraph(Graph& graph, unordered_map<uint, Station> stations) {
    graph.print();

    cout << "\nTopolog sort: ";
    vector<uint> arr = doTopologicalSort(graph);

    for (auto t: arr)
        cout << t << " ";

    cout << "\n\nStation names:\n\n";

    for (uint i = 0; i < arr.size(); i++) {
        string name = "None";
        auto t = stations.find(arr[i]);

        if (t != stations.end())
            name = t->second.getName();

        cout
            << " "
            << (i % 2 ? '\\' : '/')
            << '^'
            << (i % 2 ? '\\' : '/')
            << "  "
            << name
            << "\n";
    }


    cout << endl;

}

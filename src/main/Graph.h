#ifndef DA2_PROJETO_GRAPH_H
#define DA2_PROJETO_GRAPH_H

#include <list>
#include <vector>

using namespace std;

class Graph {
private:
    struct Edge{
        int dest;
        int duration;
        int cap;
    };

    struct Node{
        list<Edge> adj;
        bool visited;
        int pred;

    };
    int n;

public:
    vector<Node> nodes;
    Graph();
    explicit Graph(int nodes);
    void addEdge(int src, int dest, int cap, int dur);
};



#endif //DA2_PROJETO_GRAPH_H

#ifndef DA2_PROJETO_GRAPH_H
#define DA2_PROJETO_GRAPH_H

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <climits>
#include <set>

using namespace std;

class Graph {

    struct Edge {
        int dest;
        int capacity;
        int flow, revflow;
    };

    struct Node {
        list<Edge> adj;
        int mincap;
        int pred;
        int duration = 0;
        bool visited;
    };

    int n;
    bool hasDir;
    vector<Node> nodes;
    int capPath;

public:

    Graph(int nodes, bool dir): n(nodes), hasDir(dir), nodes(nodes+1) {};


    void addEdge(int src, int dest, int capacity){
        if (src<1 || src>n || dest<1 || dest>n) return;
        nodes[src].adj.push_back({dest, capacity});
        if (!hasDir) nodes[dest].adj.push_back({src, capacity});
    };

    void setDuration(int s, int dur);

    static void setCapacityPath(Edge edge, int value);

    int getCapacity() const {return this->capPath;}

    vector<Node> getNodes() {return this->nodes;}

    int getSize() const {return this->n;}

    void bfs(int v);

    void maximumCapacityPath(int s);

    int getResidCapEdge(int u, int v);

    bool hasvisited();

    int fordFelkurson();

    list<int> bfs_path(int a, int b);
};

#endif //DA2_PROJETO_GRAPH_H

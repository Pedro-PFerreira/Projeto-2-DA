#ifndef DA2_PROJETO_GRAPH_H
#define DA2_PROJETO_GRAPH_H

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <climits>
#include <set>
#include "maxHeap.h"
#include <stack>

using namespace std;

class Graph {

    struct Edge {
        bool available;
        int dest;
        int capacity;
        int flow;
        bool is_reversed;
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


    void addEdge(int src, int dest, int capacity, int  flow, bool is_reversed){
        if (src<1 || src>n || dest<1 || dest>n) return;
        nodes[src].adj.push_back({ true, dest, capacity});
        if (!hasDir) nodes[dest].adj.push_back({true, src, capacity, flow, is_reversed});
    };
    void setDuration(int s, int dur);

    int getMaxFlow();

    vector<Node> getNodes() {return this->nodes;}

    int getSize() const {return this->n;}

    bool bfs(int v);

    void maximumCapacityPath(int s, int t);

    void fordFulkerson();

    void fordFulkersonFlow(int in_flow);

    list<int> bfs_path(int a, int b);
};

#endif //DA2_PROJETO_GRAPH_H

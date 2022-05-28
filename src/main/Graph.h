#ifndef DA2_PROJETO_GRAPH_H
#define DA2_PROJETO_GRAPH_H

#include "MinHeap.h"
#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <climits>

using namespace std;

class Graph {

    struct flow {
        int origin;
        int destiny;
        int value;
    };
    struct Edge {
        int dest;
        int capacity;
        flow f[2];
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int mincap;
        int pred;
        int duration = 0;
        bool visited;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented
    int capPath;

    void dijkstra(int s) {
        MinHeap<int, int> q(n, -1);
        for (int i = 1; i <= n; i++) {
            nodes[i].mincap = INT32_MAX;
            q.insert(i, INT32_MAX);
            nodes[i].visited = false;
        }
        nodes[s].mincap = 0;
        q.decreaseKey(s, 0);
        nodes[s].pred = s;
        while (q.getSize() > 0) {
            int u = q.removeMin();
            nodes[u].visited = true;
            for (auto edge: nodes[u].adj) {
                if (!nodes[edge.dest].visited && nodes[u].mincap + edge.capacity < nodes[edge.dest].mincap) {
                    nodes[edge.dest].mincap = nodes[u].mincap + edge.capacity;
                    q.decreaseKey(edge.dest, nodes[edge.dest].mincap);
                    nodes[edge.dest].pred = u;
                }
            }
        }
    }



public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir): n(nodes), hasDir(dir), nodes(nodes+1) {
    };

    // Add edge from source to destination with a certain capacity
    void addEdge(int src, int dest, int capacity){
        if (src<1 || src>n || dest<1 || dest>n) return;
        nodes[src].adj.push_back({dest, capacity});
        if (!hasDir) nodes[dest].adj.push_back({src, capacity});
    };

    void setDuration(int s, int dur);

    void setCapacityPath(int s);

    int getCapacity() const {return this->capPath;}

    vector<Node> getNodes() const {return this->nodes;}

    int getSize() const {return this->n;}

    void bfs(int v);

    void maximumCapacityPath(int s);

    int getResidCapEdge(int u, int v);
};

#endif //DA2_PROJETO_GRAPH_H

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
        vector<Edge> adj;
        int mincap;
        int pred;
        int duration = 0;
        bool visited;
    };

    int n;
    vector<Node> nodes;
    bool hasDir;

public:

    Graph(int nodes, bool dir): n(nodes), hasDir(dir), nodes(nodes+1) {};

    // 1 src -> 3
    // 3 -> 1 src
    // 1 src -> 2
    // 2 -> 4
    // 4 -> 7 sink
    // 3 -> 5
    // 5 -> 7 sink

    void addEdge(int src, int dest, int capacity, int flow, bool is_reversed){
        if (src<1 || src>n || dest<1 || dest>n) return;
        nodes[src].adj.push_back({ true, dest, capacity, flow, is_reversed});
    };

    void addRevEdge(int src, int dest, int capacity, int flow, bool is_reversed){
        if (src<1 || src>n || dest<1 || dest>n) return;
        nodes[src].adj.push_back({ false, dest, capacity, flow, is_reversed});
    };

    void addReverseEdges() {
        for(int node = 0; node <= n; node++) {
            for(auto edge: nodes[node].adj) {
                if(!edge.is_reversed)
                    addRevEdge(edge.dest, node, edge.capacity, 0, true);
            }
        }
    }

    void setDuration(int s, int dur);

    int getMaxFlow(vector<int> path);

    vector<Node> getNodes() {return this->nodes;}

    int getSize() const {return this->n;}

    bool bfs(int v);

    int bfs_path1_2(int a, int b);

    void maximumCapacityPath(int s, int t);

    void maximumCapacityPath1_2(int s, int t);

    void edmondsKarp();

    int edmondsKarp2(int size);

    bool findReversePath(int src, int dest);

    vector<int> bfs_path(int a, int b);

    void static printPath(vector<int>& path);
};

#endif //DA2_PROJETO_GRAPH_H

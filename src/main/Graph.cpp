#include "Graph.h"

Graph::Graph() : n(0), nodes(0) {
}

Graph::Graph(int num) : n(num), nodes(num+1) {
}

void Graph::addEdge(int src, int dest, int cap, int dur) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, dur, cap});
}
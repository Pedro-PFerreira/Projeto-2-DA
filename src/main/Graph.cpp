#include "Graph.h"


void Graph::maximumCapacityPath(int s) {

    for (auto node: nodes){
        node.visited = false;
        node.mincap = 0;
    }
    nodes[s].mincap = INT16_MAX;
    nodes[s].pred = s;

    MinHeap<int, int> Q = MinHeap<int, int>(nodes.size(), -1);

    while(Q.getSize() == 0){
        int value = Q.removeMax();
        Node v = nodes[value];
        v.visited = true;
        for (auto edge : v.adj){
           int value_dest = edge.dest;
           Node w = nodes[edge.dest];
           if (!w.visited && min(v.mincap, edge.capacity) > w.mincap){
               w.mincap = min(v.mincap, edge.capacity);
               w.pred = value;
               Q.increaseKey(value_dest, w.mincap);
           }
        }
    }
}

void Graph::setDuration(int s, int dur) {nodes[s].duration = dur;}

void Graph::bfs(int v) {
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].mincap = 0;
    nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].mincap = nodes[u].mincap +1;
            }
        }
    }
}
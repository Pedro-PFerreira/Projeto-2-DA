#include "Graph.h"


void Graph::maximumCapicityPath(int s) {

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
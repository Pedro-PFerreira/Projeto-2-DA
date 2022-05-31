#include "Graph.h"

void Graph::setDuration(int s, int dur) {nodes[s].duration = dur;}

void Graph::maximumCapacityPath(int s) {

    for (auto node: nodes){
        node.visited = false;
        node.mincap = 0;
    }
    nodes[s].mincap = INT16_MAX;
    nodes[s].pred = s;

    MinHeap<int, int> Q = MinHeap<int, int>((int) nodes.size(), -1);

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
    for (int i = 0; i <= n; i++){
        capPath += nodes[i].mincap;
    }
}

void Graph::setCapacityPath(Edge edge, int value) {
    edge.capacity = value;
}

int Graph::getResidCapEdge(int u, int v) {
    for (auto edge: nodes[u].adj){
        if (edge.dest == v)
            return edge.capacity - edge.flow;
    }
    return -1;
}

void Graph::bfs(int v) {
    for (int s=1; s<=n; s++) nodes[s].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].mincap = 0;
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].mincap = nodes[u].mincap +1;
                nodes[w].pred = u;
            }
        }
    }
}

bool Graph::hasvisited() {
    bfs(1);
    return nodes[n].visited;
}

list<int> Graph::bfs_path(int a, int b){
    list<int> path;
    if (!nodes[b].visited) return path;
    path.push_back(b);
    int v = b;
    while (v != a){
        v = nodes[v].pred;
        path.push_front(v);
    }
    return path;
}

int Graph::fordFelkurson() {
    int max_capacity = 0;
    for (int i = 0; i <= n; i++){
        for (auto edge: nodes[i].adj){
            edge.flow = 0;
            edge.revflow = 0;
        }
    }

    while (!this->hasvisited()){
        list<int> path = bfs_path(1,n);
        for (int u = 1; u <= n; u++){
            if(nodes[u].visited){
                for(auto edge : nodes[u].adj){
                    int v = edge.dest;
                    if(nodes[v].visited){
                        this->setCapacityPath(edge, min(this->getResidCapEdge(u, v), edge.capacity));
                        edge.flow = edge.flow + this->getResidCapEdge(u,v);
                        edge.revflow = -edge.flow;
                    }
                }
            }

        }
        //this->maximumCapacityPath(1);
    }
    for (const Node& node : nodes){
        for (auto edge : node.adj){
            if (edge.dest == n)
                max_capacity += edge.flow;
        }
    }

    list<int> path = bfs_path(1,n);

    for (auto node : path){
        cout << node;
    }

    return max_capacity;
}



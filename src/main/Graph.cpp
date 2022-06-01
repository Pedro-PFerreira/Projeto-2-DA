#include "Graph.h"

void Graph::setDuration(int s, int dur) {nodes[s].duration = dur;}

void Graph::maximumCapacityPath(int s, int t) {
    for (Node node: nodes){
        node.pred = NULL;
        node.mincap = 0;
    }
    nodes[s].mincap = INT_MAX;
    maxHeap<int> priorQueue;
    priorQueue.push(nodes[s].mincap, s);

    while(!priorQueue.empty()){
        pair<int, int> v = priorQueue.top();
        priorQueue.pop();
        for (Edge edge : nodes[v.second].adj){
            int w = edge.dest;
            if(min(nodes[v.second].mincap, edge.capacity) > nodes[w].mincap){
                nodes[w].mincap = min(v.first, edge.capacity);
                nodes[w].pred = v.second;
                priorQueue.push(nodes[w].mincap, w);
            }
        }
    }

    cout << s << " ";
    int dest = t;
    stack<int> pilha;
    while(nodes[dest].pred != NULL){
       pilha.push(dest);
       dest = nodes[dest].pred;
    }
    cout << "Path:" << endl;
    while(!pilha.empty()){
        cout << pilha.top() << " ";
        pilha.pop();
    }
    cout << "Maximum capacity:" << endl;
    cout << endl << nodes[t].mincap;
}

int Graph::getResidCapEdge(int u, int v) {
    for (Edge edge: nodes[u].adj){
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
    cout << "Graph:" << endl;
    while (!q.empty()) {
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

void Graph::fordFulkerson() {
    int max_flow = 0;
    int path_flow = INT16_MAX;
    for (int i = 0; i <= n; i++) {
        for (Edge edge: nodes[i].adj) {
            nodes[edge.dest].pred = i;
            edge.flow = 0;
            edge.resflow = 0;
        }
    }

    while (true){
        bfs(1);
        for (int u = 1; u <= n; u++){
            if(nodes[u].visited){
                for(Edge edge : nodes[u].adj){
                    int v = edge.dest;
                    if(nodes[v].visited){
                        nodes[v].pred = u;
                        edge.capacity = min(getResidCapEdge(u, v), edge.capacity);
                        edge.flow += edge.capacity;
                        edge.resflow -= edge.flow;
                        path_flow = min(path_flow, edge.flow);
                    }
                }
                max_flow += path_flow;
            }
        }
        if (nodes[n].visited) break;
    }
    list<int> path = bfs_path(1,n);

    cout << "Path:" << endl;
    for (auto node : path){
        cout << node << " ";
    }
    cout << endl << "Maximum flow:" << max_flow << endl;
}

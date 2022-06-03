#include "Graph.h"

void Graph::setDuration(int s, int dur) {nodes[s].duration = dur;}

void Graph::maximumCapacityPath(int s, int t) { //DONE
    for (Node node: nodes){
        node.pred = 0;
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
    cout << "Path:" << endl;
    cout << s << " ";
    int dest = t;
    stack<int> pilha;
    while(nodes[dest].pred != 0){
       pilha.push(dest);
       dest = nodes[dest].pred;
    }

    while(!pilha.empty()){
        cout << pilha.top() << " ";
        pilha.pop();
    }

    cout << "Maximum capacity: ";
    cout <<  nodes[t].mincap << endl;
}

bool Graph::bfs(int v) {
    for (int s=1; s<=n; s++) nodes[s].visited = false;
    queue<int> q;
    q.push(v);
    nodes[v].visited = true;
    nodes[v].pred = -1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (Edge e : nodes[u].adj) {
            if (e.available){
                int w = e.dest;
                if (!nodes[w].visited) {
                    q.push(w);
                    nodes[w].visited = true;
                    nodes[w].pred = u;
                }
            }
        }
    }
    return nodes[n].visited;
}

list<int> Graph::bfs_path(int a, int b){
    bfs(a);
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

int Graph::getMaxFlow() {
    int max_flow = INT16_MAX;
    for (Node& node : nodes){
        for (Edge edge : node.adj){
            if (edge.available)
                max_flow = min(max_flow, edge.capacity);
        }
    }
    return max_flow;
}

void Graph::fordFulkerson() {

    int max_flow = 0;

    for (int i = 0; i <= n; i++) {
        for (Edge edge: nodes[i].adj) {
            nodes[edge.dest].pred = i;
            edge.flow = 0;
        }
    }
    list<int> path = bfs_path(1,n);
    while(bfs(1)) {
        int path_flow = getMaxFlow();
        for (int i = 1; i <= n; i++){

            vector<Edge> aux_edges;
            Edge auxEdge;
            int auxEdgeOrigin;
            for (auto edge = nodes[i].adj.begin(); edge != nodes[i].adj.end(); edge++) {
                if ((*edge).available) {
                    (*edge).capacity -= path_flow;
                    (*edge).flow = path_flow;
                    if(!(*edge).is_reversed){
                        (*edge).is_reversed = true;
                        auxEdge.available = true;
                        auxEdge.dest = i;
                        auxEdgeOrigin = edge->dest;
                        auxEdge.capacity = capPath;
                        auxEdge.flow = path_flow;
                        auxEdge.is_reversed = true;
                        aux_edges.push_back(auxEdge);
                    }

                    if ((*edge).capacity == 0) {
                        (*edge).available = false;
                    }
                }
            }
            for(auto newEdge: aux_edges) {
                addEdge(auxEdgeOrigin,auxEdge.dest,newEdge.capacity, newEdge.flow, newEdge.is_reversed);
            }

        }
    }
    cout << "Path:" << endl;
    for (auto node : path){
        cout << node << " ";
    }

    for(int i= 1; i <= n; i++){
        for(Edge edge : nodes[i].adj){
            if (edge.available) if(edge.dest == n) max_flow += edge.flow;
        }
    }

    cout << endl << "Maximum flow:" << max_flow << endl;
}

void Graph::fordFulkersonFlow(int in_flow) {
    int max_flow_allowed = getMaxFlow();

    cout << max_flow_allowed << endl;
    if (max_flow_allowed < in_flow){
        cout << "Please insert a valid_input" << endl;
        return;
    }

    for (int i = 1; i <= n; i++){
        for (auto edge = nodes[i].adj.begin(); edge != nodes[i].adj.end(); edge++){
            (*edge).capacity -= in_flow;
            (*edge).flow = in_flow;
            if ((*edge).capacity == 0){
                (*edge).available = false;
            }
        }
    }

    fordFulkerson();

}

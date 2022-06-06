#include "Graph.h"

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

    cout << "\nMaximum capacity: ";
    cout <<  nodes[t].mincap << endl;
}

void Graph::maximumCapacityPath1_2(int s, int t){
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
    int counter = 0;
    int dest = t;
    stack<int> pilha;
    while(nodes[dest].pred != 0){
        pilha.push(dest);
        dest = nodes[dest].pred;
    }

    while(!pilha.empty()){
        counter++;
        pilha.pop();
    }

    cout << "Maximum capacity: ";
    cout <<  nodes[t].mincap << endl;
    cout << "Maximum transhipment: ";
    cout << counter << endl;
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

vector<int> Graph::bfs_path(int a, int b){
    bfs(a);
    vector<int> path;
    if (!nodes[b].visited) return path;
    path.push_back(b);
    int v = b;
    while (v != a){
        v = nodes[v].pred;
        path.insert(path.begin(), v);
    }
    return path;
}

int Graph::bfs_path1_2(int a, int b){
    bfs(a);
    int counter = 0;
    vector<int> path;
    if (!nodes[b].visited) return counter;
    path.push_back(b);
    int v = b;
    while (v != a){
        v = nodes[v].pred;
        path.insert(path.begin(), v);
        counter++;
    }
    return counter;
}

void Graph::printPath(vector<int>& path){
    for (int& i : path)
        cout << i << " ";
    cout << endl;
}



int Graph::getMaxFlow(vector<int> path) {
    int max_flow = INT16_MAX;

    for (int i = 0; i < path.size() - 1; i++){
        int node = path[i];
        for (auto edge: nodes[node].adj){
            if (edge.dest == path[i+1] && edge.available){
                max_flow = min(max_flow, edge.capacity);
            }
        }
    }
    return max_flow;
}

void Graph::edmondsKarp() {

    addReverseEdges();

    int max_flow = 0;
    vector<int> path;

    for (int i = 1; i <= n; i++) {
        for (Edge edge: nodes[i].adj) {
            nodes[edge.dest].pred = i;
            edge.flow = 0;
        }
    }

    while(bfs(1)) {
        path = bfs_path(1,n);

        int path_flow = getMaxFlow(path);
        max_flow += path_flow;
        for (int i = 0; i < path.size()- 1; i++){
            int node = path[i];
            for (auto edge = nodes[node].adj.begin(); edge != nodes[node].adj.end(); edge++) {
                if ((*edge).available && (*edge).dest == path[i + 1]) {
                    if(!(*edge).is_reversed) {
                        (*edge).capacity -= path_flow;
                    } else {
                        (*edge).capacity += path_flow;
                        (*edge).available = true;
                    }

                    (*edge).flow += path_flow;

                    if ((*edge).capacity == 0) {
                        (*edge).available = false;
                    }
                }
            }
        }
    }
    printPath(path);
    cout << endl << "Maximum flow: " << max_flow << endl;
}

int Graph::edmondsKarp2(int size){

    addReverseEdges();

    int max_flow = 0;
    vector<int> path;

    for (int i = 1; i <= n; i++) {
        for (Edge edge: nodes[i].adj) {
            nodes[edge.dest].pred = i;
            edge.flow = 0;
        }
    }

    while(bfs(1)) {
        path = bfs_path(1,n);
        printPath(path);
        int path_flow = getMaxFlow(path);
        max_flow += path_flow;

        if(max_flow >= size){
            break;
        }
        for (int i = 0; i < path.size()- 1; i++){
            int node = path[i];
            for (auto edge = nodes[node].adj.begin(); edge != nodes[node].adj.end(); edge++) {
                if ((*edge).available && (*edge).dest == path[i + 1]) {
                    if(!(*edge).is_reversed) {
                        (*edge).capacity -= path_flow;
                    } else {
                        (*edge).capacity += path_flow;
                        (*edge).available = true;
                    }

                    (*edge).flow += path_flow;

                    if ((*edge).capacity == 0) {
                        (*edge).available = false;
                    }
                }
            }
        }
    }
    return max_flow;
}

int Graph::criticalPath() {

    for (int i = 1; i <= n ; i++){
        nodes[i].es = 0;
        nodes[i].pred = 0;
        nodes[i].degree = 0;
    }

    for (int i = 1; i <= n; i++){
        for (auto edge : nodes[i].adj){
            nodes[edge.dest].degree++;
        }
    }
    queue<int> s;
    for (int i = 1; i <= n ; i++){
        if (nodes[i].degree == 0)
            s.push(i);
    }
    int durMin = -1;
    while(!s.empty()) {
        int v = s.front();
        s.pop();

        if (durMin < nodes[v].es) {
            durMin = nodes[v].es;
        }
        for (auto edge: nodes[v].adj) {
            int w = edge.dest;
            if (nodes[w].es < nodes[v].es + edge.duration) {
                nodes[w].es = nodes[v].es + edge.duration;
                nodes[w].pred = v;
            }
            nodes[w].degree--;
            if (nodes[w].degree == 0)
                s.push(w);
        }
    }

    cout << "Minimum time to get the group together (units of time): " << durMin << endl;
    return durMin;
}

void Graph::maxTimeWait(int durMin) {
    addReverseEdges();

    for (int i = 1; i <= n; i++){
        nodes[i].degree = 0;
        nodes[i].lf = durMin;
    }

    for (int i = 1; i <= n; i++){
        for (auto edge : nodes[i].adj){
            if(edge.is_reversed){
                nodes[edge.dest].degree++;
            }
        }
    }
    queue<int> q;
    for (int i = 1; i <= n ; i++){
        if (nodes[i].degree == 0)
            q.push(i);
    }

    while(!q.empty()){
        int v = q.front();
        q.pop();
        for (auto edge: nodes[v].adj) {
            if(edge.is_reversed){
                int w = edge.dest;

                if (nodes[w].lf > (nodes[v].lf - edge.duration)){
                    nodes[w].lf = (nodes[v].lf - edge.duration);
                }
                nodes[w].degree--;
                if(nodes[w].degree == 0){
                    q.push(w);
                }
            }
        }
    }
    int max_ft;
    for (int i = 1; i <= n; i++){
        int ft_temp = 0, ls;
        for (auto edge : nodes[i].adj) {
            if(edge.is_reversed){
                ls = nodes[edge.dest].lf - edge.duration;
                ft_temp = ls - nodes[i].es;
                nodes[i].ft = ls - nodes[i].es;
            }
        }
        if (max_ft < ft_temp)
            max_ft = ft_temp;
    }

    cout << "Maximum time spent on waiting (hours): " << max_ft << endl;

    cout << "Locals where elements wait the maximum time:" << endl;
    for (int i = 1; i <= n; i++){
        if (nodes[i].ft == max_ft)
            cout << i << " ";
    }
}
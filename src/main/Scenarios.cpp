#include "Scenarios.h"


void Scenarios::makeGraph(const vector<Journey>& j) {
    for (auto journey : j){
        this->g.addEdge(journey.origin, journey.destiny, journey.vehicle.capacity);
        this->g.setDuration(journey.origin, journey.duration);
        this->residualGraph.addEdge(journey.origin, journey.destiny, journey.vehicle.capacity);
        this->residualGraph.setDuration(journey.origin, journey.duration);
    }
}

int Scenarios::fordFelkurson() {
    for (int i = 0; i <= g.getSize(); i++){
        for (auto edge: g.getNodes()[i].adj){
            edge.flow = 0;
            edge.revflow = 0;
        }
    }
    residualGraph = g;
    while (true){
        int n = residualGraph.getSize();
        residualGraph.bfs(1);
        if (residualGraph.getNodes()[n].visited) return residualGraph.getCapacity();
        else{
            for (int u = 1; u <= residualGraph.getSize(); u++){
                for(auto edge : residualGraph.getNodes()[u].adj){
                    int v = edge.dest;
                    residualGraph.setCapacityPath(min(residualGraph.getResidCapEdge(u, v), edge.capacity));
                    edge.flow = edge.flow + residualGraph.getResidCapEdge(u,v);
                    edge.revflow = -edge.flow;
                }
            }
            residualGraph.maximumCapacityPath(1);
        }
    }
}

int Scenarios::EdmondsKarp(Graph graph, int s, int t) {
     int max_flow = 0;
     auto nodes = graph.getNodes();
     int pred[graph.getSize()];
     while(pred[t] != NULL){
         graph.bfs(s);
         queue<int> q;
         q.push(1);

         while (!q.empty()){
             int cur = q.front();
             q.pop();
             for (auto edge : nodes[cur].adj){
                 if ((pred[edge.dest] == NULL) && (edge.dest != s) && (edge.capacity > edge.flow)){
                     pred[edge.dest] = cur;
                     q.push(edge.dest);
                 }
             }
         }

         if (pred[t] != NULL){
             int df = INT16_MAX;
             //TODO Adivinhar expressão do ciclo for
             for(;;){
                 df = min(df, edge.cap -edge.flow);
             }
             for(;;){
                 edge.flow += df;
                 edge.revflow -= df;
             }
            max_flow += df;
         }
     }

     return max_flow;
}


Scenarios::Scenarios(Graph g, Graph residual) : g(g), residualGraph(residual){
    FileReader fileReader = FileReader("../input/in01_b.txt");
    this->journeys = fileReader.getJourneys();
    makeGraph(this->journeys);
}

Graph Scenarios::getG() {return this->g;}

void Scenarios::unseparateGroups() {
    g.maximumCapacityPath(1);
}

void Scenarios::separateGroups() {}
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
            edge.f[0] ={i, edge.dest, 0};
            edge.f[1] = {edge.dest, i, 0};
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
                    edge.f[0] = {u,v, edge.f[0].value + residualGraph.getResidCapEdge(u,v)};
                    edge.f[1] = {v,u, -edge.f[0].value};
                }
            }
            residualGraph.maximumCapacityPath(1);
        }
    }
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
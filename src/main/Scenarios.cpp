#include "Scenarios.h"

void Scenarios::makeGraph(const vector<Journey>& j) {
    for (auto journey : j){
        this->g.addEdge(journey.origin, journey.destiny, journey.vehicle.capacity, 0, false);
        this->g.setDuration(journey.origin, journey.duration);
    }
}

Scenarios::Scenarios(Graph& g) : g(g), residualGraph(g) {
    FileReader fileReader = FileReader("../input/afonso.txt");
    this->journeys = fileReader.getJourneys();
    makeGraph(this->journeys);
}

Graph Scenarios::getG() {return this->g;}

void Scenarios::UGmaxCapacity() { //1.1
   g.maximumCapacityPath(1, g.getSize());
}

void Scenarios::UGoptimal() {
    cout << "The optimal solutions will be between these values: " << endl;
    g.bfs1_2(1, g.getSize());
    g.maximumCapacityPath1_2(1, g.getSize());
}

void Scenarios::separateGroups() {
    residualGraph = g;
    residualGraph.edmondsKarp();
    //residualGraph.fordFulkersonFlow(3);
}
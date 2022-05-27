#include "Scenarios.h"


void Scenarios::makeGraph(const vector<Journey>& j) {
    for (auto journey : j){
        this->g.addEdge(journey.origin, journey.destiny, journey.vehicle.capacity);
        this->g.setDuration(journey.origin, journey.duration);
    }

}

Scenarios::Scenarios(Graph g) : g(g) {
    FileReader fileReader = FileReader("../input/in01_b.txt");
    this->journeys = fileReader.getJourneys();
    makeGraph(this->journeys);
}

Graph Scenarios::getG() {return this->g;}

void Scenarios::unseparateGroups() {
    g.maximumCapacityPath(1);
}

void Scenarios::separateGroups() {}
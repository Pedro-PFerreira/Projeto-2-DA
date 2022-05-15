#include "Scenarios.h"


void Scenarios::makeGraph(const vector<Journey>& j, int num_locals) {
    this->g = Graph(num_locals);
    for (auto journey : j){
        this->g.addEdge(journey.origin, journey.destiny, journey.capacity, journey.duration);
    }

}

Scenarios::Scenarios() {
    FileReader fileReader = FileReader("../input/in01.txt");
    this->journeys = fileReader.getJourneys();
    makeGraph(this->journeys, fileReader.getNumLocals());
}

Graph Scenarios::getG() {return this->g;}

void Scenarios::unseparateGroups() {}

void Scenarios::separateGroups() {}
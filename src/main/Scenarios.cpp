#include "Scenarios.h"


void Scenarios::makeGraph(const vector<Journey>& j) {
    for (auto journey : j){
        this->g.addVertex(journey.origin);
        this->g.findVertex(journey.origin)->setDuration(journey.duration);
        this->g.addVertex(journey.destiny);
        this->g.addEdge(journey.origin, journey.destiny, journey.capacity);
    }

}

Scenarios::Scenarios() {
    FileReader fileReader = FileReader("../input/in01.txt");
    this->journeys = fileReader.getJourneys();
    makeGraph(this->journeys);
}

Graph<int> Scenarios::getG() {return this->g;}

void Scenarios::unseparateGroups() {}

void Scenarios::separateGroups() {}
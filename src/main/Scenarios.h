#ifndef DA2_PROJETO_SCENARIOS_H
#define DA2_PROJETO_SCENARIOS_H


#include "FileReader.h"
#include "Elements.h"
#include "Graph.h"

#include <vector>

using namespace std;

class Scenarios {

private:
    vector<Journey> journeys;

    Graph g;

    void makeGraph(const vector<Journey>& j);

public:
    Scenarios(Graph g);

    void unseparateGroups();

    void separateGroups();

    Graph getG();

};


#endif //DA2_PROJETO_SCENARIOS_H

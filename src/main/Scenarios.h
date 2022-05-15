#ifndef DA2_PROJETO_SCENARIOS_H
#define DA2_PROJETO_SCENARIOS_H


#include "FileReader.h"
#include "Journey.h"
#include "Graph.h"

#include <vector>

using namespace std;

class Scenarios {

private:
    vector<Journey> journeys;

    Graph g;

    void makeGraph(const vector<Journey>& j, int num_locals);

public:
    Scenarios();

    void unseparateGroups();

    void separateGroups();

    Graph getG();

};


#endif //DA2_PROJETO_SCENARIOS_H

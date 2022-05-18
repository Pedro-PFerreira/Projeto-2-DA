#ifndef DA2_PROJETO_SCENARIOS_H
#define DA2_PROJETO_SCENARIOS_H


#include "FileReader.h"
#include "Elements.h"
#include "Graph.h"

#include <vector>

using namespace std;

class Scenarios {

private:
    vector<Elements> journeys;

    Graph<int> g;

    void makeGraph(const vector<Elements>& j);

public:
    Scenarios();

    void unseparateGroups();

    void separateGroups();

    Graph<int> getG();

};


#endif //DA2_PROJETO_SCENARIOS_H

#ifndef DA2_PROJETO_SCENARIOS_H
#define DA2_PROJETO_SCENARIOS_H


#include "FileReader.h"
#include "Elements.h"
#include "Graph.h"

#include <vector>
#include <list>
#include <queue>

using namespace std;

class Scenarios {

private:
    vector<Journey> journeys;

    Graph g, residualGraph;

    void makeGraph(const vector<Journey>& j);

    //int EdmondsKarp(Graph graph, int s, int t);
public:
    explicit Scenarios(Graph& g);

    Graph getG();

    void UGmaxCapacity(); //unseparate group max capacity

    void UGoptimal();

    void separateGroups();

};


#endif //DA2_PROJETO_SCENARIOS_H

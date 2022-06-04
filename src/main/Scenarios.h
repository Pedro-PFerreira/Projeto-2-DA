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
    /**
     * Group of journeys that will be made.
     */
    vector<Journey> journeys;

    /**
     * Main graph that will connect all the journeys.
     */
    Graph g;
    /**
     * Residual graph of the main graph.
     */
    Graph residualGraph;

    /**
     * This method will create the main graph, so that we can create its residual graph.
     * @param j Group of journeys that will be connected.
     */
    void makeGraph(const vector<Journey>& j);

    /**
     * Maximum flow possible for the residual graph.
     */
    int max_flow = 0;

public:
    /**
     * Scenarios constructor. It reads a file thanks to a FileReader and creates of the graph of the journeys contained on that file.
     * @param g graph of the journeys contained on a file.
     */
    explicit Scenarios(Graph& g);

    /**
     *
     * @return main graph.
     */
    Graph getG();
    
    void UGmaxCapacity(); //unseparate group max capacity

    void UGoptimal();

    void separatedGroups();

    void pathForGroup(int size);

    void pathForResizedGroup(int size);
};


#endif //DA2_PROJETO_SCENARIOS_H

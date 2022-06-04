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

    /**
     * This method obtains the path that has the maximum capacity, that is, the lowest capacity between the graph's edges.
     * In this case, the groups of people won't separate, they go all together.
     */
    void UGmaxCapacity();
    /**
     * This method shows the possible paths that can have the same or lowest maximum capacity, but no transhipments; or that have the zero or more transhipments, but more capacity.
     */
    void UGoptimal();

    /**
     * This method shows the residual graph's maximum flow.
     * It also shows a corrected path to a given group's dimension input, in case the previous path doesn't fit it.
     */
    void separatedGroups();

    /**
     * It also shows a corrected path to a given group's dimension input, in case the the maximum flow path doesn't fit it.
     * @param size Group's dimension.
     */
    void pathForGroup(int size);

    /**
     * This method shows all the possible paths for a resized group. If the maximum flow allowed in the residual graph is greater than
     * the new group's dimension, then it only shows the maximum flow's path.
     * @param size New group's dimension.
     */
    void pathForResizedGroup(int size);
};


#endif //DA2_PROJETO_SCENARIOS_H

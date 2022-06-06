#include "Scenarios.h"

void Scenarios::makeGraph(const vector<Journey>& j) {
    for (auto journey : j){
        this->g.addEdge(journey.origin, journey.destiny, journey.vehicle.capacity, 0, false, journey.duration);
    }
}

Scenarios::Scenarios(Graph& g) : g(g), residualGraph(g) {
FileReader fileReader = FileReader("../input/mega.txt");
    this->journeys = fileReader.getJourneys();
    makeGraph(this->journeys);
}

Graph Scenarios::getG() {return this->g;}

void Scenarios::UGmaxCapacity() { //1.1
    cout << "/--------------- UNSEPARATED GROUPS ---------------/\n" << endl;
    cout << "/--------------- MAXIMUM CAPACITY PATH ---------------/\n" << endl;
   g.maximumCapacityPath(1, g.getSize());
}

void Scenarios::UGoptimal(){
    cout << "\n/--------------- OPTIMAL SOLUTIONS ---------------/\n" << endl;
    cout << "The optimal solutions will be between these values: " << endl;
    vector<int> path = g.bfs_path(1, g.getSize());
    int min_cap = g.getMaxFlow(path);
    int transhipments = g.bfs_path1_2(1, g.getSize());
    cout << "Minimum capacity: " << min_cap << endl;
    cout << "Minimum transhipments: " << transhipments << endl;
    g.maximumCapacityPath1_2(1, g.getSize());

}

void Scenarios::separatedGroups() {
    cout << "\n/--------------- MAXIMUM FLOW PATH, USING EDMONDS KARP---------------/\n" << endl;
    residualGraph = g;
    cout << "Maximum flow path:" << endl;
    residualGraph.edmondsKarp();
}

void Scenarios::pathForGroup(int size) {
    cout << "\n/--------------- SEPARATED GROUPS ---------------/" << endl;

    cout << "Paths for this group size " << size << " people: " << endl;
    residualGraph = g;
    max_flow = residualGraph.edmondsKarp2(size);
}

void Scenarios::pathForResizedGroup(int size) {
    residualGraph = g;
    if(max_flow >= size){
        cout << "Previous path works for this group size" << endl;
        return;
    }
    else{
        cout << "Paths for this resized group: " << endl;
        residualGraph.edmondsKarp2(size);
    }
}

void Scenarios::pathForCritical(){
    cout << "\n/--------------- CRITICAL SIZE PATH, USING LAST FINISH ---------------/\n" << endl;
    residualGraph = g;
    durMin = residualGraph.criticalPath();
}

void Scenarios::pathLatestFinish(){
    residualGraph = g;
    residualGraph.maxTimeWait(durMin);
}
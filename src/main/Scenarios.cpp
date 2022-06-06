#include "Scenarios.h"

void Scenarios::makeGraph(const vector<Journey>& j) {
    for (auto journey : j){
        this->g.addEdge(journey.origin, journey.destiny, journey.vehicle.capacity, 0, false);
        this->g.setDuration(journey.origin, journey.duration);
    }
}

Scenarios::Scenarios(Graph& g) : g(g), residualGraph(g) {
FileReader fileReader = FileReader("../input/in01_b.txt");
    this->journeys = fileReader.getJourneys();
    makeGraph(this->journeys);
}

Graph Scenarios::getG() {return this->g;}

void Scenarios::UGmaxCapacity() { //1.1
   g.maximumCapacityPath(1, g.getSize());
}

void Scenarios::UGoptimal(){
    cout << "The optimal solutions will be between these values: " << endl;
    vector<int> path = g.bfs_path(1, g.getSize());
    int min_cap = g.getMaxFlow(path);
    int transhipments = g.bfs_path1_2(1, g.getSize());
    cout << "Minimum capacity: " << min_cap << endl;
    cout << "Minimum transhipments: " << transhipments << endl;
    g.maximumCapacityPath1_2(1, g.getSize());

}

void Scenarios::separatedGroups() {
    residualGraph = g;
    cout << "EDMONDS-KARP\nPossible Paths:" << endl;
    residualGraph.edmondsKarp();
    residualGraph.edmondsKarp2(3);
}

void Scenarios::pathForGroup(int size) {
    cout << "Paths for this group size: " << endl;
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
    g.criticalPath();
}
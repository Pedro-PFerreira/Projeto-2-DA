#include "../test/Test.cpp"
#include "FileReader.h"
#include "Scenarios.h"

using namespace std;

int main() {
    FileReader fileReader = FileReader("../input/in03_b.txt");

    Graph g = Graph(fileReader.getNumLocals(), true);

    Scenarios scenarios = Scenarios(g);
    scenarios.UGmaxCapacity();
    cout << "FORD-FULKERSON" << endl;
    scenarios.separateGroups();

    return 0;
}

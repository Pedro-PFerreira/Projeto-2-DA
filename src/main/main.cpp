#include "../test/Test.cpp"
#include "FileReader.h"
#include "Scenarios.h"

using namespace std;

int main() {
    FileReader fileReader = FileReader("../input/in05_b.txt");

    Graph g = Graph(fileReader.getNumLocals());

    Scenarios scenarios = Scenarios(g);
    scenarios.UGmaxCapacity(); // 1.1
    scenarios.UGoptimal(); // 1.2

    scenarios.pathForGroup(5); //2.1
    scenarios.pathForResizedGroup(10); //2.2
    scenarios.separatedGroups(); // 2.3

    scenarios.pathForCritical();

    return 0;
}

#include "../test/Test.cpp"
#include "FileReader.h"
#include "Scenarios.h"

using namespace std;

int main() {
    FileReader fileReader = FileReader("../input/in01_b.txt");

    Graph g = Graph(fileReader.getNumLocals(), true);

    Scenarios scenarios = Scenarios(g);
    scenarios.unseparateGroups();
    /*scenarios.separateGroups();*/
    return 0;
}

#include "gtest/gtest.h"
#include "../main/FileReader.h"
#include "../main/Scenarios.h"

using namespace std;

TEST(TEST_1, checkReadFile){
    FileReader fileReader = FileReader("../input/in01_b.txt");
    vector<Journey> viagens = fileReader.getJourneys();

    cout << viagens[0].origin << endl;
    cout << viagens.size() << endl;

    ASSERT_EQ(136, viagens.size());
}

TEST(TEST_2, checkGraphs){

    FileReader fileReader = FileReader("../input/in01_b.txt");

    Scenarios scenarios = Scenarios(Graph(fileReader.getNumLocals(), true));

    int counter = 0;

    for (const auto& node: scenarios.getG().getNodes()){
        counter += node.adj.size();
    }


    ASSERT_EQ(fileReader.getNumLocals(), scenarios.getG().getNodes().size() - 1);
    ASSERT_EQ(fileReader.getNumJourneys(), counter);
}

TEST(TEST_3,checkIfGraphAndResidualGraphHaveDifferentAddresses) {
    FileReader fileReader = FileReader("../input/in01_b.txt");
    Scenarios scenarios(Graph(fileReader.getNumLocals(),true));

    scenarios.unseparateGroups();
}
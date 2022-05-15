#include "gtest/gtest.h"
#include "../main/FileReader.h"
#include "../main/Scenarios.h"
#include "../main/Graph.h"

using namespace std;

TEST(TEST_1, checkReadFile){
    FileReader fileReader = FileReader("../input/in01.txt");
    vector<Journey> viagens = fileReader.getJourneys();

    cout << viagens[0].origin << endl;
    cout << viagens.size() << endl;

    ASSERT_EQ(146, viagens.size());
}

TEST(TEST_2, checkGraphs){

    FileReader fileReader = FileReader("../input/in01.txt");

    Scenarios scenarios = Scenarios();

    int counter = 0;

    for (const auto& node: scenarios.getG().nodes){
        counter += (int) node.adj.size();
    }

    ASSERT_EQ(fileReader.getNumLocals()+ 1, scenarios.getG().nodes.size());
    ASSERT_EQ(fileReader.getNumJourneys(), counter);
}

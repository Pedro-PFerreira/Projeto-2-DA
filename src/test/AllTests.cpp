#include "gtest/gtest.h"
#include "../main/FileReader.h"
#include "../main/Scenarios.h"

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

    for (const auto& vertex: scenarios.getG().getVertexSet()){
        counter += vertex->getAdj().size();
    }

    ASSERT_EQ(fileReader.getNumLocals(), scenarios.getG().getNumVertex());
    ASSERT_EQ(fileReader.getNumJourneys(), counter);
}

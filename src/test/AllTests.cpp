#include "gtest/gtest.h"
#include <string>
#include "../main/FileReader.h"

using namespace std;

TEST(TEST_1, checkReadFile){
    FileReader fileReader = FileReader("../input/in10.txt");
    vector<Journey> viagens = fileReader.getJourneys();

    cout << viagens[0].origin << endl;
    cout << viagens.size() << endl;

    ASSERT_EQ(49487, viagens.size());
}

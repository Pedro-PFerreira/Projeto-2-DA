#include <iostream>
#include "gtest/gtest.h"

class Test {
public:
    Test();
private:
    static int runTests();
};

Test::Test() {
    runTests();
}

int Test::runTests() {
    std::cout << "Running all tests..." << std::endl;
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

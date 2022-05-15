cmake_minimum_required(VERSION 3.17)
project(DA2_PROJETO)

# Build the Google tests
set(GOOGLETEST_PATH lib/googletest-master)
add_subdirectory(${GOOGLETEST_PATH})

add_executable(DA2_PROJETO src/main/main.cpp src/main/FileReader.cpp src/main/FileReader.h src/main/Journey.h)

add_executable(DA2_PROJETO-Tests src/main/FileReader.cpp src/main/FileReader.h src/main/Journey.h src/test/Test.cpp src/test/AllTests.cpp)


target_link_libraries(DA2_PROJETO gtest_main gmock_main)
target_link_libraries(DA2_PROJETO-Tests gtest_main gmock_main)

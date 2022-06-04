cmake_minimum_required(VERSION 3.17)
project(DA2_PROJETO)

# Build the Google tests
set(GOOGLETEST_PATH lib/googletest-master)
add_subdirectory(${GOOGLETEST_PATH})

add_executable(DA2_PROJETO src/main/main.cpp src/main/FileReader.cpp src/main/FileReader.h src/main/Elements.h src/main/Scenarios.cpp src/main/Scenarios.h src/main/Graph.h src/main/Graph.cpp src/main/maxHeap.h)

add_executable(DA2_PROJETO-Tests src/main/FileReader.cpp src/main/FileReader.h src/main/Elements.h src/main/Scenarios.cpp src/main/Scenarios.h src/test/Test.cpp src/test/AllTests.cpp src/main/Graph.h src/main/Graph.cpp src/main/maxHeap.h)


target_link_libraries(DA2_PROJETO gtest_main gmock_main)
target_link_libraries(DA2_PROJETO-Tests gtest_main gmock_main)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/output/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)
#ifndef DA2_PROJETO_FILEREADER_H
#define DA2_PROJETO_FILEREADER_H

#include "Elements.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class FileReader{
private:
  string dirPath;
  int num_locals, num_journeys;


public:
    FileReader();

    explicit FileReader(string dir);

    vector<Elements> getJourneys();

    int getNumLocals() const;

    int getNumJourneys() const;
};

#endif //DA2_PROJETO_FILEREADER_H

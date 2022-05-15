#ifndef DA2_PROJETO_FILEREADER_H
#define DA2_PROJETO_FILEREADER_H

#include "Journey.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class FileReader{
private:
  string dirPath;

public:
    FileReader(string dir);

    vector<Journey> getJourneys();

};

#endif //DA2_PROJETO_FILEREADER_H

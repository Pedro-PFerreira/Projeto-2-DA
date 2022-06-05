#ifndef DA2_PROJETO_FILEREADER_H
#define DA2_PROJETO_FILEREADER_H

#include "Elements.h"
#include "Graph.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class FileReader{
private:
    /**
    * String that contains the file to be read's path.
    */
    string dirPath;
    /**
    * Number of existent locals.
    */
    int num_locals;
    /**
    * Number of possible journeys.
    */
    int num_journeys;


public:
    /**
    * Class constructor.
    * @param dir is a string that contains the path of the file to be read.
    */
    explicit FileReader(string dir);

    /**
    * Method that reads the corresponding file os dirPath. Then, it will collects each journey's data.
    * @return a vector with all information of company's couriers.
    */
    vector<Journey> getJourneys();

    /**
     * @return Number of existent locals.
     */
    int getNumLocals() const;

    /**
     *
     * @return Number of possible journeys.
     */
    int getNumJourneys() const;
};

#endif //DA2_PROJETO_FILEREADER_H

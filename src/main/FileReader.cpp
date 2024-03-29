#include "FileReader.h"

#include <utility>

FileReader::FileReader(string dir) {
    this->dirPath = move(dir);
    ifstream file;
    file.open(dirPath);
    string Locals, Travel;
    if(!file){
        cout << "Unable to open file!\n";
        cout << "The program will now close.\n";
        system(reinterpret_cast<const char *>(EXIT_FAILURE));
    }
    else if(file.is_open()){
        getline(file, Locals, ' ');
        getline(file, Travel, '\n');
        this->num_locals = stoi(Locals);
        this->num_journeys = stoi(Travel);
        file.close();
    }
}

int FileReader::getNumLocals() const {return this->num_locals;}

int FileReader::getNumJourneys() const {return this->num_journeys;}

vector<Journey> FileReader::getJourneys() {
    ifstream file;
    vector<Journey> journeys;
    string line, Origin, Dest, Cap, Dur;
    file.open(dirPath);
    int count = 0;
    if(!file){
        cout << "Unable to open file!\n";
        cout << "The program will now close.\n";
        system(reinterpret_cast<const char *>(EXIT_FAILURE));
    }
    else if(file.is_open()){
        getline(file, line, '\n');
        while(count < getNumJourneys()){
            getline(file, Origin, ' ');
            getline(file, Dest, ' ');
            getline(file, Cap, ' ');
            getline(file, Dur, '\n');

            int origin = stoi(Origin), dest = stoi(Dest), cap = stoi(Cap), dur = stoi(Dur);

            Journey journey{};
            journey.origin = origin;
            journey.destiny = dest;
            journey.vehicle.capacity = cap;
            journey.duration = dur;
            journeys.push_back(journey);
            count++;
        }
        file.close();
    }
    return journeys;
}

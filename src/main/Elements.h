#ifndef DA2_PROJETO_ELEMENTS_H
#define DA2_PROJETO_ELEMENTS_H


using namespace std;

struct Vehicle {
    int capacity;
};

struct Journey {
    Vehicle vehicle;
    int origin, destiny, duration;
};


#endif //DA2_PROJETO_ELEMENTS_H

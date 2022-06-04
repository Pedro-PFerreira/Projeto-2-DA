#ifndef DA2_PROJETO_ELEMENTS_H
#define DA2_PROJETO_ELEMENTS_H


using namespace std;

/**
 * Agency's vehicle.
 */
struct Vehicle {
    /**
     * Vehicle's capacity (number of people it can carry).
     */
    int capacity;
};

/**
 * Vehicle's journeys.
 */
struct Journey {
    /**
     * vehicle associated to that journey.
     */
    Vehicle vehicle;
    /**
     * Local where the journey starts.
     */
    int origin;
    /**
     * Destination's local of the journey.
     */
    int destiny;
    /**
     * Journey's duration.
     */
    int duration;
};


#endif //DA2_PROJETO_ELEMENTS_H

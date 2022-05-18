#include "Vehicle.h"

Vehicle::Vehicle(int departure, int arrival, int capacity, int time) : departure(departure), arrival(arrival),
                                                                       capacity(capacity), time(time) {}

int Vehicle::getDeparture() const {
    return departure;
}

int Vehicle::getArrival() const {
    return arrival;
}

int Vehicle::getCapacity() const {
    return capacity;
}

int Vehicle::getTime() const {
    return time;
}

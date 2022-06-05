#include "StopVehicle.h"


vector<int> Stop::getAdj() const{
    return adj;
}

void Stop::addVehicle(int vehicle){
    adj.push_back(vehicle);
}

void Stop::setVisited(bool visited) {
    Stop::visited = visited;
}

bool Stop::isVisited() const {
    return visited;
}

void Stop::setAdj(const vector<int> &adj) {
    Stop::adj = adj;
}

int Stop::getDistance() const {
    return distance;
}

void Stop::setDistance(int distance) {
    Stop::distance = distance;
}

int Stop::getPred() const {
    return pred;
}

void Stop::setPred(int pred) {
    Stop::pred = pred;
}

int Stop::getMaxCapacity() const {
    return maxCapacity;
}

void Stop::setMaxCapacity(int maxCapacity) {
    Stop::maxCapacity = maxCapacity;
}

int Stop::getPeople() const{
    return people;
}

void Stop::setPeople(int people){
    Stop::people = people;
}

int Stop::getLatestArrival() const {
    return latest_arrival;
}

void Stop::setLatestArrival(int latestArrival) {
    latest_arrival = latestArrival;
}

int Stop::getEarliestArrival() const {
    return earliest_arrival;
}

void Stop::setEarliestArrival(int earliestArrival) {
    earliest_arrival = earliestArrival;
}

Vehicle::Vehicle(int origin,int dest,int capacity,int time) : origin(origin), dest(dest),capacity(capacity), time(time){}

int Vehicle::getOrigin() const {
    return origin;
}
int Vehicle::getDest() const {
    return dest;
}
int Vehicle::getCapacity() const {
    return capacity;
}
int Vehicle::getTime() const {
    return time;
}
int Vehicle::getFlow() const {
    return flow;
}

void Vehicle::setFlow(int flow) {
    Vehicle::flow = flow;
}

void Vehicle::setCapacity(int capacity) {
    Vehicle::capacity = capacity;
}

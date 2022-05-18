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




Vehicle::Vehicle(const int origin, const int dest, const int capacity, const int time) : origin(origin), dest(dest),
                                                                                         capacity(capacity), time(time) {}
const int Vehicle::getOrigin() const {
    return origin;
}
int Vehicle::getDest() const {
    return dest;
}
const int Vehicle::getCapacity() const {
    return capacity;
}
const int Vehicle::getTime() const {
    return time;
}
int Vehicle::getFlow() const {
    return flow;
}

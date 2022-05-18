//
// Created by igcbs on 16/01/2022.
//

#ifndef STOP_EDGE_H
#define STOP_EDGE_H

#include <string>
#include <vector>

/*
 *
 *
 * */

using namespace std;

class Vehicle;

class Stop {
private:
    vector<int> adj;
    bool visited;

public:
    vector<int> getAdj() const;
    void addVehicle(int vehicle);
    bool isVisited() const;
    void setVisited(bool visited);
};

class Vehicle{
private:
    const int origin;
    const int dest;      // Destination node // An integer weight
    const int capacity;
    const int time;
    int flow = 0;            //temporary variable, not const

public:
    Vehicle(const int origin, const int dest, const int capacity, const int time);
    int getDest() const;
    const int getCapacity() const;
    const int getTime() const;
    int getFlow() const;

    const int getOrigin() const;
};

#endif //STOP_EDGE_H

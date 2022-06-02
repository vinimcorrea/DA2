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
    int distance;
    int pred;
    int maxCapacity;
    int people;

public:
    vector<int> getAdj() const;
    void addVehicle(int vehicle);
    bool isVisited() const;
    void setVisited(bool visited);

    void setAdj(const vector<int> &adj);

    int getDistance() const;

    void setDistance(int distance);

    int getPred() const;

    void setPred(int pred);

    int getMaxCapacity() const;

    void setMaxCapacity(int maxCapacity);

    int getDepth();

    int getPeople();

    void setPeople(int people);

    void setDepth(int depth);

    int depth;
};

class Vehicle{
private:
    Vehicle(const int origin, const int dest, const int capacity, const int time, const int depth);

    const int origin;
    const int dest;      // Destination node // An integer weight
    int capacity;
    int time;
    int flow = 0;            //temporary variable, not const

public:
    Vehicle(const int origin, const int dest, const int capacity, const int time);
    int getDest() const;
    int getCapacity() const;
    int getTime() const;
    int getFlow() const;

    void setFlow(int flow);
    void setCapacity(int capacity);



    const int getOrigin() const;

    int depth;

    int getDepth(int depth);

    void setDepth(int depth);
};

#endif //STOP_EDGE_H

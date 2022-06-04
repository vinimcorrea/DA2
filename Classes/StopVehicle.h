#ifndef STOP_EDGE_H
#define STOP_EDGE_H

#include <string>
#include <vector>

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
    int latest_arrival;
    int earliest_arrival;

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

    int getPeople();

    void setPeople(int people);

    int getLatestArrival() const;

    void setLatestArrival(int latestArrival);

    int getEarliestArrival() const;

    void setEarliestArrival(int earliestArrival);


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
};

#endif

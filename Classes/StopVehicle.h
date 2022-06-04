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
    int latest_departure;
    int max_wait;

public:
    vector<int> getAdj() const;
    bool isVisited() const;
    int getDistance() const;
    int getPred() const;
    int getMaxCapacity() const;
    int getPeople() const;
    int getLatestArrival() const;
    int getEarliestArrival() const;
    int getLatestDeparture() const;
    int getMaxWait() const;

    void setAdj(const vector<int> &adj);
    void setVisited(bool visited);
    void setDistance(int distance);
    void setPred(int pred);
    void setMaxCapacity(int maxCapacity);
    void setPeople(int people);
    void setLatestArrival(int latestArrival);
    void setEarliestArrival(int earliestArrival);
    void setLatestDeparture(int latestDeparture);
    void setMaxWait(int maxWait);

    void addVehicle(int vehicle);
    void emptyAdj();
};

class Vehicle{
private:
    int origin;
    int dest;      // Destination node // An integer weight
    int capacity;
    int time;
    int flow = 0;            //temporary variable, not const
public:
    Vehicle(int origin, int dest, int capacity, int time);
    int getDest() const;
    int getCapacity() const;
    int getTime() const;
    int getFlow() const;
    int getOrigin() const;

    void setFlow(int flow);
    void setCapacity(int capacity);

    void invert();
};

#endif

//
// Created by igcbs on 16/01/2022.
//

#ifndef STOP_EDGE_H
#define STOP_EDGE_H

#include <string>
#include <list>

using namespace std;

class Edge;

class Stop {
private:
    list<int> adj;
    int distance;


public:
    Stop();
    Stop(const string &code, const string &name, const string &zone, float latitude, float longitude);
    ~Stop();
    const string &getCode() const;
    const string &getName() const;
    const string &getZone() const;
    float getLatitude() const;
    float getLongitude() const;
    int getDistance()const;
    bool getVisited() const;
    const list<Edge> &getAdj() const;
    void setCode(const string &code);
    void setDistance(int distance);
    void setVisited(bool visites);
    void setName(const string &name);
    void setZone(const string &zone);
    void setLatitude(float latitude);
    void setLongitude(float longitude);
    friend istream &operator>>(istream &is, Stop &stop);
    void addEdge(Edge edge);
    Stop(int x, int y);
    bool operator==(Stop s);
};

class Edge{
private:
    Stop dest;   // Destination node
    int weight; // An integer weight
    string lineCode;
public:
    Edge(Stop dest,int weight, string lineCode);
     Stop getDest() const;
    int getWeight() const;
    string getLineCode();
    void setDest(Stop dest);
    void setWeight(int weight);
    void setLineCode(string lineCode);


};

#endif //STOP_EDGE_H

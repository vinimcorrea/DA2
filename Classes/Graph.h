

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include "StopVehicle.h"

using namespace std;

class Graph {
    int totalStops;
    int totalVehicles;
    vector<Vehicle> vehicles;
    vector<Stop> stops;

public:
    Graph(int fileNumber);
    void readNetwork(int fileNumber);
    void readStops();


    // Depth-First Search: example implementation
    void dfs(int v);
    // Breadth-First Search: example implementation
    void bfs(int v);


    int distance(Stop a, Stop b);

    void bfsDist(Stop v);
    int dijkstra_distance (Stop a, Stop b);
    int getIndexStop(string code);
};

#endif

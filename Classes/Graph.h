

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include "StopVehicle.h"
#include "maxHeap.h"
#include "minHeap.h"

using namespace std;

class Graph {
    int totalStops;
    int totalVehicles;
    int fileIndex;
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

    int minimumTransshipments(int s, int t);


    void bfsDist(int v);

    bool existPath(int a, int b);

    int fordFulkerson(int s, int t);

    void addVehicle(int src, int dest, int capacity, int duration);


    int dijkstra_distance (Stop a, Stop b);
    int getIndexStop(string code);


    int maximumCapacityWays(int s, int t);
    int setDistance(int s);

    int fordFulkerson(int s, int t, int given);

    void bfsprint(int s, int t, int given);

    void depthInit(int x);
};

#endif

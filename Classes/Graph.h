

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <utility>
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

    vector<pair<int, int>> pathFlowDuration;

public:
    Graph(int fileNumber);
    void readNetwork(int fileNumber);
    void readStops();


    // Depth-First Search: example implementation
    void dfs(int v);
    // Breadth-First Search: example implementation
    void bfs(int v);

    int minimumTransshipments(int s, int t); // 1.2


    void bfsDist(int v);

    bool existPath(int a, int b);

    int fordFulkerson(int s, int t);

    void addVehicle(int src, int dest, int capacity, int duration);


    int dijkstra_distance (Stop a, Stop b);
    int getIndexStop(string code);


    int maximumCapacityWays(int s, int t); // 1.1
    int setDistance(int s);
    void bfsprint(int s, int given);

    int fordFulkerson(int s, int t, int given); //2.1 & 2.3
    int fordFulkersonNonZeroFlow(int s, int t, int units); //2.2
    void makeResidualGraph();

    int getMinDuration(int s, int t,int people);

    int stopOutwardFlow(int s);

    vector<pair<int, int>> getPath() const;

    int minDuration(int s, int t);//2.4
};

#endif

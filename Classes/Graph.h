

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
    vector<Vehicle> vehicles;
    int fileIndex;
    vector<Stop> stops;

public:
    Graph(int fileNumber);

    void readNetwork(int fileNumber);
    void readStops();

    void bfs(int v);

    void makeResidualGraph();
    void transposeGraph();

    bool pathExists(int a, int b);
    void addVehicle(int src, int dest, int capacity, int duration);
    int determineWaitTimes(int s, int t, vector<int>& waiting_stops);
    int stopOutwardFlow(int s);

    int unsplitGroupFindMaxSize(int s, int t); // 1.1
    int unsplitGroupFindMinTransfers(int s, int t); // 1.2
    int splitGroupFindPath(int s, int t, int given=INT32_MAX); //2.1 & 2.3
    int splitGroupEnlargedGroup(int s, int t, int units); //2.2
    int splitGroupFindMinDuration(int s, int t);//2.4
    int splitGroupFindWaitTimes(int s, int t, vector<int>& waiting_stops);//2.5

    void printPath(int s, int given);
    void printOne(int s, int t);
};

#endif

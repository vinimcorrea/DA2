

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
    ///
    /// \param fileNumber file number in format "inXX.txt"
    /// Reads the attributes on the provided source file
    ///
    void readNetwork(int fileNumber);
    ///
    /// Reads the stops and vehicles, building the graph
    ///
    void readStops();
    ///
    /// \param v starting node
    /// bfs algorithm from starting node
    ///
    void bfs(int v);
    ///
    /// creates the residual graph for the Ford Fulkerson algorithms
    ///
    void makeResidualGraph();
    ///
    /// \param a starting node
    /// \param b ending node
    /// \return checks if a path exits from a to b
    ///
    bool pathExists(int a, int b);
    ///
    /// \param src
    /// \param dest
    /// \param capacity
    /// \param duration
    /// Creates a new vehicle using the given arguments
    ///
    void addVehicle(int src, int dest, int capacity, int duration);
    ///
    /// \param s starting node
    /// \return returns the sum of the flow values of adjacent nodes of s
    int stopOutwardFlow(int s);
    ///
    /// \param s starting node
    /// \param t ending node
    /// \return path with max size of a group without splitting it
    int unsplitGroupFindMaxSize(int s, int t); // 1.1
    ///
    /// \param s starting node
    /// \param t ending node
    /// \return path with minimium transfers of a group without splitting it
    int unsplitGroupFindMinTransfers(int s, int t); // 1.2
    ///
    /// \param s starting node
    /// \param t ending node
    /// \param given size of group
    /// \return path of a group splitting it if needed
    int splitGroupFindPath(int s, int t, int given=INT32_MAX); //2.1 & 2.3
    ///
    /// \param s starting node
    /// \param t ending node
    /// \param units units to increase group size
    /// \return path of a group increasing its size and splitting it if needed
    int splitGroupEnlargedGroup(int s, int t, int units); //2.2
    ///
    /// \param s starting node
    /// \param t ending node
    /// \return path with minimium transfers of a group splitting it if needed
    int splitGroupFindMinDuration(int s, int t);//2.4
    ///
    /// \param s starting node
    /// \param t ending node
    /// \param waiting_stops stops the group will need to wait
    /// \return the wait times of a group splitting it if needed
    int splitGroupFindWaitTimes(int s, int t, vector<int>& waiting_stops);//2.5
    ///
    /// \param s starting node
    /// \param given size of group
    /// prints the path of a group using a bfs algorithm
    void printPath(int s, int given);
    ///
    /// \param s starting node
    /// \param t ending node
    /// prints the path of a group that doesn't split
    void printOne(int s, int t);
};

#endif

//
// Created by 35196 on 24/01/2022.
//
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

#include "Graph.h"

using namespace std;

#define TESTS_FOLDER "Tests/"


string filename(int i){
    if(i > 10 || i < 1)
        printf("file not found\n");
    if(i < 10){
        return "in0" + to_string(i) + ".txt";
    }
    return "in" + to_string(i) + ".txt";
}

Graph::Graph(int fileIndex){
    readNetwork(fileIndex);
    readStops(); //Iterates through edges vector creating adjacency list for the stops, creates stops vector
}

void Graph::readNetwork(int fileNumber){
    string file = TESTS_FOLDER + filename(fileNumber);
    ifstream networkFile(file);

    if(networkFile.fail()){
        cerr << "file error\n";
    }

    /* network attributes*/
    string numNodes, numVehicles;

    /* trip attributes*/
    string departure, arrival, capacity, duration;

    getline(networkFile, numNodes, ' ');
    cout << "total number of nodes: " << numNodes << endl;
    getline(networkFile, numVehicles);
    cout << "total number of vehicles: " << numVehicles << endl;


    while(getline(networkFile, departure, ' ')){
        cout << "departure: " << departure << endl;
        getline(networkFile, arrival, ' ');
        cout << "arrival: " << arrival << endl;
        getline(networkFile, capacity, ' ');
        cout << "capacity: " << capacity << endl;
        getline(networkFile, duration);
        Vehicle e1(stoi(departure), stoi(arrival), stoi(capacity), stoi(duration));
        vehicles.push_back(e1);
    }

    totalStops = stoi(numNodes);
    totalVehicles = stoi(numVehicles);

}

void Graph::readStops(){
    for(int i=1; i <=totalStops; i++){
        Stop a;
        stops.push_back(a);
    }
    for(int i=0; i<totalVehicles; i++){
        stops[vehicles[i].getOrigin()].addVehicle(i);
    }
}

// Depth-First Search: example implementation
void Graph::dfs(int w) {
    stops[w].setVisited(true) ;
    for (int i = 0; i < stops[w].getAdj().size(); i++){
        int u = vehicles[i].getDest();
        if (stops[w].isVisited())
            dfs(w);
    }
}

// Depth-First Search: example implementation
void Graph::bfs(int x) {
    for (int v=1; v<=totalStops; v++) stops[v].setVisited(false);
    queue<int> q; // queue of unvisited nodes
    q.push(x);
    stops[x].setVisited(true);
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        for (auto e : stops[u].getAdj()) {
            int w = vehicles[e].getDest();
            if (!stops[w].isVisited()) {
                q.push(w);
                stops[w].setVisited(true);
            }
        }
    }
}


// bfs algorithm
/*
void Graph::bfsDist(Stop x){
    x.setDistance(0);
    for (int v=1; v<=n; v++) stops[v].setVisited(false);
    queue<Stop> q; // queue of unvisited nodes
    q.push(x);
    x.setVisited(true);
    while (!q.empty()) { // while there are still unvisited nodes
        Stop u = q.front(); q.pop();
        for (auto &e : u.getAdj()) {
            Stop w = e.getDest();
            if (!w.getVisited()) {
                q.push(w);
                w.setVisited(true);
                w.setDistance(u.getDistance()+1);
            }
        }
    }

}
*/

//dijkstra algorithm
/*
int Graph::dijkstra_distance(Stop a, Stop b) {
    if (a==b) return 0;
    for(int i = 1; i <= n; i++) {
        stops[i].setDistance(INT_MAX);
        stops[i].setVisited(false);
    }
    a.setDistance(0);
    MinHeap<string,int> q(n,NULL);
    for (int i = 1; i<=n;i++){
        q.insert(stops[i].getCode(),stops[i].getDistance());
    }
    while (q.getSize()!=0){
        string u = q.removeMin();
        int x= getIndexStop(u);
        stops[x].setVisited(true);
        for (auto & edge : stops[x].getAdj()){
            if ( (stops[x].getDistance() + edge.getWeight() < edge.getDest().getDistance()) && q.hasKey(edge.getDest().getCode())  ){
                stops[getIndexStop(edge.getDest().getCode())].setDistance(stops[x].getDistance()+edge.getWeight());
                q.decreaseKey(edge.getDest().getCode(),stops[getIndexStop(edge.getDest().getCode())].getDistance());
            }
        }

    }
    if (b.getDistance()==INT_MAX) return -1;
    return b.getDistance();
}
*/
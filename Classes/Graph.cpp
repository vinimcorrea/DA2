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
    if(i < 10){
        return "in0" + to_string(i) + ".txt";
    }
    return "in" + to_string(i) + ".txt";
}

Graph::Graph(int fileIndex){
    this->fileIndex = fileIndex;
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
    getline(networkFile, numVehicles);

    while(getline(networkFile, departure, ' ')){
        getline(networkFile, arrival, ' ');
        getline(networkFile, capacity, ' ');
        getline(networkFile, duration);
        Vehicle e1(stoi(departure), stoi(arrival), stoi(capacity), stoi(duration));
        vehicles.push_back(e1);
    }

    totalStops = stoi(numNodes);
    totalVehicles = stoi(numVehicles);

}

void Graph::readStops(){
    for(int i=0; i <=totalStops; i++){
        Stop a;
        stops.push_back(a);
    }
    for(int i=0; i<totalVehicles; i++){
        stops[vehicles[i].getOrigin()].addVehicle(i);
    }
}

void Graph::addVehicle(int src, int dest, int capacity, int duration) {
    if (src < 0 || src > totalStops || dest < 0 || dest > totalStops){
        cout << "\nCan't add edge. Invalid bound.\n" << endl;
        return;
    }
    Vehicle v1(src, dest, capacity, duration);
    vehicles.push_back(v1);

    vector<int> adjs = stops[src].getAdj();
    adjs.push_back(vehicles.size() -1);
    stops[src].setAdj(adjs);

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
    stops[x].setPred(-1);
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        for (auto e : stops[u].getAdj()) {
            int w = vehicles[e].getDest();
            if (!stops[w].isVisited() && vehicles[e].getCapacity() > 0) {
                q.push(w);
                stops[w].setVisited(true);
                stops[w].setPred(u);
            }
        }
    }
}

int Graph::maximumCapacityWays(int s, int t) {
    MaxHeap<int, int> maxHeap = MaxHeap<int, int>(totalStops,-1);

    for(int v=1; v <= totalStops; v++){
        if(v == s) continue;
        stops[v].setMaxCapacity(0);
        stops[v].setPred(0);
        maxHeap.insert(v, 0);
    }

    stops[s].setMaxCapacity(INT32_MAX);
    maxHeap.insert(s, -stops[s].getMaxCapacity());

    while(maxHeap.getSize()){
        int v = maxHeap.removeMax();
        for(int e =0; e < stops[v].getAdj().size(); e++){
            int r = stops[v].getAdj()[e];
            int w = vehicles[r].getDest();
            int minCap = min(stops[v].getMaxCapacity(), vehicles[r].getCapacity());
            int maxCap = stops[w].getMaxCapacity();
            if(minCap > maxCap){
                stops[w].setMaxCapacity(minCap);
                stops[w].setPred(v);
                maxHeap.increaseKey(w, -stops[w].getMaxCapacity());
            }
        }
    }

    return stops[t].getMaxCapacity();
}


int Graph::minimumTransshipments(int s, int t){
    if(!existPath(s, t)){
        cerr << "\nDoesn't exist a path from " << s << " to " << t << endl;
        return -1;
    }

    MinHeap<int, int> minHeap = MinHeap<int, int>(totalStops,-1);
    for (int v = 1; v <= totalStops; v++) {
        if(v == s) {
            continue;
        }
        stops[v].setDistance(INT32_MAX);
        stops[v].setPred(0);
        minHeap.insert(v,INT32_MAX);
    }
    stops[s].setDistance(0);
    minHeap.insert(s,stops[s].getDistance());
    int v;
    while(minHeap.getSize()) {
        v = minHeap.removeMin();
        for(auto e : stops[v].getAdj()) {
            int w = vehicles[e].getDest();
            if((stops[v].getDistance() + 1) < stops[w].getDistance()) {
                stops[w].setDistance(stops[v].getDistance() + 1);
                stops[w].setPred(v);
                minHeap.decreaseKey(w, stops[w].getDistance());
            }
        }
    }
    return stops[t].getDistance()-1;
}



// bfs algorithm

void Graph::bfsDist(int x){
    stops[x].setDistance(0);
    for (int v=1; v<=totalStops; v++) stops[v].setVisited(false);
    queue<int> q; // queue of unvisited nodes
    q.push(x);
    stops[x].setVisited(true);
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        for (auto &e : stops[u].getAdj()) {
            int w = vehicles[e].getDest();
            if (!stops[w].isVisited()) {
                q.push(w);
                stops[w].setVisited(true);
                stops[w].setDistance(stops[u].getDistance()+1);
            }
        }
    }

}

bool Graph::existPath(int a, int b) {
    bfs(a);
    return stops[b].isVisited();
}
int Graph::stopOutwardFlow(int s){
    int adder=0;
    for(auto e : stops[s].getAdj()){
        adder+=vehicles[e].getFlow();
    }
    return adder;
}

int Graph::getMinDuration(int source, int sink, int people) {
    fordFulkerson(source, sink, people);
    int duration = 0;

    for(auto &e : pathFlowDuration){
        people -= e.first;
        duration = max(duration, e.second);
    }

    if(people > 0){
        cerr << "Unable to join those people together" << endl;
    }

    return duration;
}

void Graph::makeResidualGraph(){
    for(int i=0; i<stops.size();i++){
        for(auto e : stops[i].getAdj()){
            int flow = vehicles[e].getFlow();
            if(flow > 0){
                vehicles[e].setCapacity(vehicles[e].getCapacity() - flow);
                int dest = vehicles[e].getDest();
                bool oppositeEdgeExists=false;
                for(auto e2 : stops[dest].getAdj()){
                    if(vehicles[e2].getDest() == i){
                        vehicles[e2].setCapacity(vehicles[e2].getCapacity() + flow);
                        oppositeEdgeExists=true;
                        break;
                    }
                }
                if(!oppositeEdgeExists){
                    addVehicle(dest, i, flow, 0);
                    //TODO: Change Duration from 0
                }
            }

        }
    }
}

int Graph::fordFulkersonNonZeroFlow(int s, int t, int units){
    int init_flow = stopOutwardFlow(s);
    int max_flow = init_flow;
    // 1. Create the residual graph. (Same as the original graph.)
    Graph residualGraph = *this;
    residualGraph.makeResidualGraph();
    // 2. Keep calling BFS to check for an augmenting path from the source to the sink...
    while(residualGraph.existPath(s, t)){
        // 3. Find the max flow through the path we just found.
        int path_flow = INT32_MAX;

        int duration = 0;
        // Go through the path we just found. Iterate through the path.
        int v = t;
        while(v != s){

            int u = residualGraph.stops[v].getPred(); // The parent.

            // Update the path flow to this capacity if it's smaller
            for(auto &e : residualGraph.stops[u].getAdj()){
                if(residualGraph.vehicles[e].getDest() == v){
                    path_flow = min(path_flow, residualGraph.vehicles[e].getCapacity());
                    duration += residualGraph.vehicles[e].getTime();
                }
            }

            // Setup for the next edge in the path.
            v = u;
        }
        // 4. Update the residual capacities of the edges and reverse edges.
        v = t;
        while(v != s){
            int u = residualGraph.stops[v].getPred(); // The parent.

            for(auto &e : residualGraph.stops[u].getAdj()){
                if(residualGraph.vehicles[e].getDest() == v){
                    residualGraph.vehicles[e].setCapacity(residualGraph.vehicles[e].getCapacity() - path_flow);
                    vehicles[e].setFlow(vehicles[e].getFlow() + path_flow);
                    //maybe residualGraph?
                }
            }
            bool hasReverseEdge = false;
            for(auto &e : residualGraph.stops[v].getAdj()){
                if(residualGraph.vehicles[e].getDest() == u){
                    hasReverseEdge=true;
                    residualGraph.vehicles[e].setCapacity(residualGraph.vehicles[e].getCapacity() + path_flow);
                    //vehicles[e].setFlow(path_flow);
                    //maybe residualGraph?
                    break;
                }
            }
            if(!hasReverseEdge){
                residualGraph.addVehicle(v, u, path_flow, 0);
                //TODO: Change Time from 0
            }
            // Setup for the next edge in the path.
            v = u;
        }
        max_flow += path_flow;
        if(max_flow >= init_flow + units){
            bfsprint(s, init_flow + units);
            return max_flow;
        }

    }
    cout << "Could not find a path for the group, the max flow is: " << max_flow;
    return max_flow;
}

int Graph::fordFulkerson(int s, int t, int given=INT32_MAX) {
    vector<pair<int, int>> paths;
    int max_flow = 0;
    for(int i = 0; i < totalVehicles; i++){
        vehicles[i].setFlow(0);
    }
    // 1. Create the residual graph. (Same as the original graph.)
    Graph residualGraph = *this;

    // 2. Keep calling BFS to check for an augmenting path from the source to the sink...
    while(residualGraph.existPath(s, t)){

        // 3. Find the max flow through the path we just found.
        int path_flow = INT32_MAX;

        int duration = 0;
        // Go through the path we just found. Iterate through the path.
        int v = t;
        while(v != s){

            int u = residualGraph.stops[v].getPred(); // The parent.

            // Update the path flow to this capacity if it's smaller
            for(auto &e : residualGraph.stops[u].getAdj()){
                if(residualGraph.vehicles[e].getDest() == v){
                    path_flow = min(path_flow, residualGraph.vehicles[e].getCapacity());
                    duration += residualGraph.vehicles[e].getTime();
                }
            }

            // Setup for the next edge in the path.
            v = u;
        }
        cout << "path: "<< path_flow <<" " << "duration: " << duration << endl;
        paths.push_back({path_flow, duration});
        // 4. Update the residual capacities of the edges and reverse edges.
        v = t;
        while(v != s){
            int u = residualGraph.stops[v].getPred(); // The parent.

            for(auto &e : residualGraph.stops[u].getAdj()){
                if(residualGraph.vehicles[e].getDest() == v){
                    residualGraph.vehicles[e].setCapacity(residualGraph.vehicles[e].getCapacity() - path_flow);
                    vehicles[e].setFlow(vehicles[e].getFlow() + path_flow);
                    //maybe residualGraph?
                }
            }
            bool hasReverseEdge = false;
            for(auto &e : residualGraph.stops[v].getAdj()){
                if(residualGraph.vehicles[e].getDest() == u){
                    hasReverseEdge=true;
                    residualGraph.vehicles[e].setCapacity(residualGraph.vehicles[e].getCapacity() + path_flow);
                    //vehicles[e].setFlow(path_flow);
                    //maybe residualGraph?
                    break;
                }
            }
            if(!hasReverseEdge){
                residualGraph.addVehicle(v, u, path_flow, 0);
                //TODO: Change Time from 0
            }
            // Setup for the next edge in the path.
            v = u;
        }
        max_flow += path_flow;
        if(max_flow >= given){
            this->pathFlowDuration = paths;
            bfsprint(s, given);
            return max_flow;
        }

    }
    this->pathFlowDuration = paths;

    if(given == INT32_MAX){
        bfsprint(s,given);
        cout << "Max flow is: " << max_flow;
        return max_flow;
    }
    cout << "Could not find a path for the group, the max flow is: " << max_flow;
    return max_flow;
}

void Graph::bfsprint(int s, int given){
    for (int v=1; v<=totalStops; v++) stops[v].setPeople(0);
    for (int v=1; v<=totalStops; v++) stops[v].setVisited(false);
    queue<int> q; // queue of unvisited nodes
    q.push(s);
    stops[s].setVisited(true);
    stops[s].setPeople(given);
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        for (auto &e : stops[u].getAdj()) {
            int w = vehicles[e].getDest();
            if(vehicles[e].getFlow() > 0 && stops[u].getPeople() > 0){
                int peopleSent = min(vehicles[e].getFlow(), stops[u].getPeople());
                cout << "From: " << vehicles[e].getOrigin() << " To: " << vehicles[e].getDest()
                     << " Quantity: " << peopleSent << endl;
                stops[u].setPeople(stops[u].getPeople() - peopleSent);
                stops[w].setPeople(stops[w].getPeople() + peopleSent);
                stops[w].setVisited(false);
            }
            if (!stops[w].isVisited()) {
                q.push(w);
                stops[w].setVisited(true);
            }
        }
        cout << "----------------------------------------------------------------" << endl;
    }
}

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
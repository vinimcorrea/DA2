#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>

#include "Graph.h"

using namespace std;

#define TESTS_FOLDER "Tests/"


string filename(int i){
    if(i < 10){
        return "in0" + to_string(i) + ".txt";
    }
    return "in" + to_string(i) + ".txt";
}

Graph::Graph(int fileNumber){
    fileIndex = fileNumber;
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

int Graph::unsplitGroupFindMaxSize(int s, int t) {
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


int Graph::unsplitGroupFindMinTransfers(int s, int t){
    if(!pathExists(s, t)){
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

bool Graph::pathExists(int a, int b) {
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

int Graph::splitGroupFindMinDuration(int s, int t){
    for (int v=1; v<=totalStops; v++) stops[v].setVisited(false);
    for(auto &stop :stops){
        stop.setEarliestArrival(INT32_MAX);
        stop.setLatestArrival(0);
    }
    stops[s].setEarliestArrival(0);
    stops[s].setLatestArrival(0);
    stops[s].setVisited(true);
    queue<int> q; // queue of unvisited nodes
    q.push(s);
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        for (auto &e: stops[u].getAdj()) {
            if(vehicles[e].getFlow() != 0){
                int w = vehicles[e].getDest();
                if (stops[w].getEarliestArrival() > stops[u].getEarliestArrival() + vehicles[e].getTime()) {
                    stops[w].setEarliestArrival(stops[u].getLatestArrival() + vehicles[e].getTime());
                    stops[w].setVisited(false);
                }
                if (stops[w].getLatestArrival() < stops[u].getLatestArrival() + vehicles[e].getTime()) {
                    stops[w].setLatestArrival(stops[u].getLatestArrival() + vehicles[e].getTime());
                    stops[w].setVisited(false);
                }
                if (!stops[w].isVisited()) {
                    q.push(w);
                    stops[w].setVisited(true);
                }
            }
        }
    }
    return(stops[t].getLatestArrival());
}

int Graph::splitGroupFindWaitTimes(int s, int t, vector<int>& waiting_stops){
    for (int v=1; v<=totalStops; v++) stops[v].setVisited(false);
    for(auto &stop :stops){
        stop.setEarliestArrival(INT32_MAX);
        stop.setLatestArrival(0);
    }
    stops[s].setEarliestArrival(0);
    stops[s].setLatestArrival(0);
    stops[s].setVisited(true);
    queue<int> q; // queue of unvisited nodes
    q.push(s);
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        for (auto &e: stops[u].getAdj()) {
            if(vehicles[e].getFlow() != 0){
                int w = vehicles[e].getDest();
                if (stops[w].getEarliestArrival() > stops[u].getLatestArrival() + vehicles[e].getTime()) {
                    stops[w].setEarliestArrival(stops[u].getLatestArrival() + vehicles[e].getTime());
                    stops[w].setVisited(false);
                }
                if (stops[w].getLatestArrival() < stops[u].getLatestArrival() + vehicles[e].getTime()) {
                    stops[w].setLatestArrival(stops[u].getLatestArrival() + vehicles[e].getTime());
                    stops[w].setVisited(false);
                }
                if (!stops[w].isVisited()) {
                    q.push(w);
                    stops[w].setVisited(true);
                }
            }
        }
    }
    int maxWaitTime=0;
    for (int v=1; v<=totalStops; v++) {
        int waitTime = stops[v].getLatestArrival() - stops[v].getEarliestArrival();
        if(waitTime > maxWaitTime){
            maxWaitTime = waitTime;
        }
    }
    for (int v=1; v<=totalStops; v++) {
        if(stops[v].getLatestArrival() - stops[v].getEarliestArrival() == maxWaitTime){
            waiting_stops.push_back(v);
        }
    }
    return maxWaitTime;
}

int Graph::splitGroupEnlargedGroup(int s, int t, int units){
    int init_flow = stopOutwardFlow(s);
    int max_flow = init_flow;
    // 1. Create the residual graph. (Same as the original graph.)
    Graph residualGraph = *this;
    residualGraph.makeResidualGraph();
    // 2. Keep calling BFS to check for an augmenting path from the source to the sink...
    while(residualGraph.pathExists(s, t)){
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
                }
            }
            bool hasReverseEdge = false;
            for(auto &e : residualGraph.stops[v].getAdj()){
                if(residualGraph.vehicles[e].getDest() == u){
                    hasReverseEdge=true;
                    residualGraph.vehicles[e].setCapacity(residualGraph.vehicles[e].getCapacity() + path_flow);
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
            printPath(s, init_flow + units);
            return max_flow;
        }

    }
    cout << "Could not find a path for the group, the max flow is: " << max_flow;
    return max_flow;
}

int Graph::splitGroupFindPath(int s, int t, int given) {
    int max_flow = 0;
    for(int i = 0; i < totalVehicles; i++){
        vehicles[i].setFlow(0);
    }
    // 1. Create the residual graph. (Same as the original graph.)
    Graph residualGraph = *this;

    // 2. Keep calling BFS to check for an augmenting path from the source to the sink...
    while(residualGraph.pathExists(s, t)){

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
                }
            }
            bool hasReverseEdge = false;
            for(auto &e : residualGraph.stops[v].getAdj()){
                if(residualGraph.vehicles[e].getDest() == u){
                    hasReverseEdge=true;
                    residualGraph.vehicles[e].setCapacity(residualGraph.vehicles[e].getCapacity() + path_flow);
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
            printPath(s, given);
            return max_flow;
        }

    }
    if(given == INT32_MAX){
        cout << "----------------------------------------------------------------" << endl;
        printPath(s, given);
        //cout << "Max flow is: " << max_flow;
        return max_flow;
    }
    cout << "Could not find a path for the group, the max flow is: " << max_flow;
    return max_flow;
}

void Graph::printPath(int s, int given){
    for (int v=1; v<=totalStops; v++) stops[v].setPeople(0);
    for (int v=1; v<=totalStops; v++) stops[v].setVisited(false);
    queue<int> q; // queue of unvisited nodes
    q.push(s);
    stops[s].setVisited(true);
    stops[s].setPeople(given);
    bool printed; // to avoid line spam
    while (!q.empty()) { // while there are still unvisited nodes
        printed = false;
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
                printed = true;
            }
            if (!stops[w].isVisited()) {
                q.push(w);
                stops[w].setVisited(true);
            }
        }
        if(printed) cout << "----------------------------------------------------------------" << endl;
    }
}

void Graph::printOne(int s, int t){
    stack<int> path;
    path.push(t);
    int current = t;
    while(current != s){
        current = stops[current].getPred();
        path.push(current);
    }
    //cout << "The path is:" << endl;
    while(!path.empty()){
        cout << path.top() << " ";
        path.pop();
    }
    cout << endl;
}

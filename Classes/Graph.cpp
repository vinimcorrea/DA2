//
// Created by 35196 on 24/01/2022.
//


#include "Graph.h"

Graph::Graph() {
    this->n=0;
    stops={};
}
// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir){
    stops.push_back(Stop());
}

void Graph::addStop(Stop &stop) {
    this->stops.push_back(stop);
}
// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, Stop& dest, int weight,string code) {
    if (src<1 || src>n ) return;
    stops[src].addEdge(Edge(dest,weight,code));
    if (!hasDir) dest.addEdge(Edge(dest,weight,code));
}

// Depth-First Search: example implementation
void Graph::dfs(Stop& w) {
    w.setVisited(true) ;
    for (auto &e : w.getAdj()) {
        Stop w = e.getDest();
        if (w.getVisited())
            dfs(w);
    }
}

// Depth-First Search: example implementation
void Graph::bfs(Stop& x) {
    for (int v=1; v<=n; v++) stops[v].setVisited(false);
    queue<Stop> q; // queue of unvisited nodes
    q.push(x);
    x.setVisited(true);
    while (!q.empty()) { // while there are still unvisited nodes
        Stop u = q.front(); q.pop();
        for (auto e : u.getAdj()) {
            Stop w = e.getDest();
            if (!w.getVisited()) {
                q.push(w);
                w.setVisited(true);
            }
        }
    }
}



// ----------------------------------------------------------
// Exercicio 2: Componentes conexos
// ----------------------------------------------------------

// ..............................
// a) Contando componentes conexos
// TODO
int Graph::connectedComponents() {
    for (int v=1; v<=n; v++) stops[v].setVisited(false);
    int res = 0;
    for (int i=1 ; i<n;i++){
        if (!stops[i].getVisited()){
            res++;
            visitando(stops[i]);
        }
    }
    return res;
}

void Graph::visitando(Stop& v){
    v.setVisited(true);
    for (auto e : v.getAdj()) {
        Stop w = e.getDest();
        if (!w.getVisited())
            visitando(w);
    }
}


// ----------------------------------------------------------
// Exercicio 3: Ordenacao topologica
// ----------------------------------------------------------
// TODO
list<Stop> Graph::topologicalSorting() {
    list<Stop> order;
    for(int i = 1; i <= n; i++)
        stops[i].setVisited(false);
    for(int i = 1; i <= n; i++){
        if(!stops[i].getVisited()){
            dfsTopo(stops[i], order);
        }
    }
    return order;
}
void Graph::dfsTopo(Stop& v, list<Stop>& order) {
    v.setVisited(true);
    for(auto &e : v.getAdj()){
        Stop w = e.getDest();
        if(!w.getVisited())
            dfsTopo(w, order);
    }
    order.push_front(v);
}

// ..............................
// a) Distancia entre dois nos
// TODO
int Graph::distance(Stop a, Stop b) {
    if(a == b) return 0;
    for(int i = 1; i <= n; i++)
        stops[i].setDistance(-1);
    bfsDist(a);
    return b.getDistance();
}
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

int Graph::getIndexStop(string code) {
    for(int i=1;i<=n;i++){
        if(stops[i].getCode()==code){
            return i;
        }
    }
    return -1;
}
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




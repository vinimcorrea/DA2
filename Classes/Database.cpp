#include "Database.h"
#include "Vehicle.h"

#include <iostream>
#include <fstream>

#include <string>


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


Network Database::readNetwork(int fileNumber){
    string file = TESTS_FOLDER + filename(fileNumber);
    ifstream networkFile(file);

    vector<Vehicle> net;


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
        Vehicle v1(stoi(departure), stoi(arrival), stoi(capacity), stoi(duration));
        net.push_back(v1);
    }

    Network n1(stoi(numNodes), stoi(numVehicles), net);

    return n1;
}




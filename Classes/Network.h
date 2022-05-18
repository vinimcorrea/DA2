#ifndef SECOND_PROJECT_NETWORK_H
#define SECOND_PROJECT_NETWORK_H

#include "Vehicle.h"

#include <vector>

using namespace std;

class Network {
    int totalNodes;
    int totalVehicles;
    vector<Vehicle> net;

public:
    Network(int totalNodes, int totalVehicles, const vector<Vehicle> &net);

    int getTotalNodes() const;

    int getTotalVehicles() const;

    const vector<Vehicle> &getNet() const;
};


#endif //SECOND_PROJECT_NETWORK_H

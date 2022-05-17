#include "Network.h"


int Network::getTotalNodes() const {
    return totalNodes;
}

int Network::getTotalVehicles() const {
    return totalVehicles;
}

const vector<Vehicle> &Network::getNet() const {
    return net;
}

Network::Network(int totalNodes, int totalVehicles, const vector<Vehicle> &net) : totalNodes(totalNodes),
                                                                                  totalVehicles(totalVehicles),
                                                                                  net(net) {}

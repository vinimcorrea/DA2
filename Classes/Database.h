#ifndef SECOND_PROJECT_DATABASE_H
#define SECOND_PROJECT_DATABASE_H

#include <vector>
#include "Vehicle.h"
#include "Network.h"
#include "StopEdge.h"

using namespace std;


class Database {


public:
    Network readNetwork(int fileNumber);

};

#endif //SECOND_PROJECT_DATABASE_H

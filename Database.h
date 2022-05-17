#ifndef SECOND_PROJECT_DATABASE_H
#define SECOND_PROJECT_DATABASE_H

#include "Vehicle.h"
#include "Network.h"
#include <vector>

using namespace std;

class Database {


public:
    Network readNetwork(int fileNumber);

};


#endif //SECOND_PROJECT_DATABASE_H

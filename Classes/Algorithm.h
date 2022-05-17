//
// Created by duart on 17/05/2022.
//

#ifndef SECOND_PROJECT_ALGORITHM_H
#define SECOND_PROJECT_ALGORITHM_H


#include "Database.h"
#include <vector>

using namespace std;

/**
 * @brief Basic class with the database and one method to solve each of the 2 cases in scenario 1 and each of the 5 cases in scenario 2
 *
 */
class Algorithm {
    Database db;

    /**
     * Solves scenario 1(Groups do not separate), case 1 -  Find maximum group size possible from a given origin to a destiny
     * on a graph, and find a possible route the group can take to its destination
     * @param origin - index of the origin on the graph
     * @param dest - index of the destiny on the graph
     * @param *route - vector of stops, indicating the route to be taken by the group. Returned by reference
     * @return max group size from origin to dest
     */

    int scenario1_max_group_dim(int origin, int dest, vector<int>* route);
};


#endif //SECOND_PROJECT_ALGORITHM_H

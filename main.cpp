#include "Classes/Graph.h"

int main() {
    Graph g1(0);

    cout << "Max group dimension: " << g1.maximumCapacityWays(1, 4) << endl;

    cout << "Min transshipments: " << g1.minimumTransshipments(1, 4) << endl;

    //g1.fordFulkerson(1, 4, 12);

    g1.fordFulkerson(1, 4,6);


    return 0;
}

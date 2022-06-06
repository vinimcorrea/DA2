#include "Classes/Graph.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "Classes/Algorithm.h"

using namespace std;

void wait(){
    using namespace std::this_thread;
    using namespace std::chrono;
    sleep_for(seconds(1));
}

int main() {
    while(true) {
        int gindex;
        int start;
        int end;
        int given;
        int units;
        int dummy;
        wait();
        cout <<
             "|============================================================================|\n"
             "|     ______ _    __ ____   ______ ____   ___     _   __ _____  ____ ______  |\n"
             "|    / ____/| |  / //  _/  /_  __// __ \\ /   |   / | / // ___/ /  _//_  __/  |\n"
             "|   / __/   | | / / / /     / /  / /_/ // /| |  /  |/ / \\__ \\  / /   / /     |\n"
             "|  / /___   | |/ /_/ /     / /  / _, _// ___ | / /|  / ___/ /_/ /   / /      |\n"
             "| /_____/   |___//___/    /_/  /_/ |_|/_/  |_|/_/ |_/ /____//___/  /_/       |\n"
             "|                                                                            |\n"
             "|============================================================================|\n"
             "|      Scenario 1.1                    [11]                                  |\n"
             "|      Scenario 1.2                    [12]                                  |\n"
             "|      Scenario 2.1                    [21]                                  |\n"
             "|      Scenario 2.2                    [22]                                  |\n"
             "|      Scenario 2.3                    [23]                                  |\n"
             "|      Scenario 2.4                    [24]                                  |\n"
             "|      Scenario 2.5                    [25]                                  |\n"
             "|      Exit                            [0]                                   |\n"
             "|============================================================================|\n";

        cout << endl;
        cout << "Choose an option: ";
        int choice;

        cin >> choice;
        if (cin.fail() || cin.peek() != '\n' || (choice != 11 && choice != 12 && choice != 21 && choice != 22 && choice != 23 && choice != 24 && choice != 25 && choice != 0)) {
            //^ I know I know, dont judge me
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input!" << endl;
            wait();
            continue;
        }
        cout << endl;
        if(choice == 0) {cout << "Goodbye :)"; wait(); exit(0);}
        cout << "Please input the following values:";
        cout << "Graph (1 - 10): " ;
        cin >> gindex;
        Graph g1(gindex);
        cout << "Starting stop (index): ";
        cin >> start;
        cout << "Ending stop (index): " ;
        cin >> end;

        switch (choice)
        {
            case 11:
                cout << endl;
                given = g1.unsplitGroupFindMaxSize(start, end);
                cout << "The max group size is: " << given << endl;
                cout << "The path is: ";
                g1.printOne(start,end);
                cout << endl;
                break;
            case 12:
                cout << endl;
                given = g1.unsplitGroupFindMaxSize(start, end);
                cout << "The max group size is: " << given << endl;
                cout << "The max capacity path is: ";
                g1.printOne(start,end);
                cout << endl;
                given = g1.unsplitGroupFindMinTransfers(start, end);
                if(given > 0) {
                    cout << "The necessary size is: " << given << endl;
                    cout << "The minimum transfers path is: ";
                    g1.printOne(start, end);
                    cout << endl;
                    break;
                }
                cout << "No alternative path" << endl;
                cout << endl;
                break;
            case 21:
                cout << "Group size: " ;
                cin >> given;
                cout << endl;
                cout << "Path: " << endl;
                g1.splitGroupFindPath(start, end, given);
                cout << endl;
                break;
            case 22:
                cout << "Group size: " ;
                cin >> given;
                    cout << "Increase by: " ;
                cin >> units;
                cout << endl;
                cout << "Initial path: " << endl;
                g1.splitGroupFindPath(start, end, given);
                cout << endl;
                cout << "Corrected path: " << endl;
                g1.splitGroupEnlargedGroup(start, end, units);
                cout << endl;
                break;
            case 23:
                cout << endl;
                cout << "Path: " << endl;
                dummy = g1.splitGroupFindPath(start, end);
                cout << endl;
                cout << "Max Group Size: " << dummy << endl;
                cout << endl;
                break;
            case 24:
                cout << "Group size: " ;
                cin >> given;
                cout << endl;
                cout << "Path: " << endl;
                g1.splitGroupFindPath(start, end, given);
                cout << endl;
                cout << "The group will meet again after " << g1.splitGroupFindMinDuration(start, end) << " units of time" << endl;
                cout << endl;
                break;
            case 25:
                cout << "Group size: " ;
                cin >> given;
                cout << endl;
                cout << "Path: " << endl;
                g1.splitGroupFindPath(start, end, given);
                vector<int> waiting_stops;
                cout << endl;
                cout << "Max Wait Time: " << g1.splitGroupFindWaitTimes(start, end, waiting_stops) << endl;
                cout << "At stops: ";
                int i;
                for(i=0; i<waiting_stops.size()-1; i++){
                    cout << waiting_stops[i] << ", ";
                }
                cout << waiting_stops[i] << endl;
                cout << endl;
                break;
        }
        wait();
        wait();
    }
}

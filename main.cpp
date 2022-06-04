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
             "|      Scenario 1.1                    [11]                                   |\n"
             "|      Scenario 1.2                    [12]                                   |\n"
             "|      Scenario 2.1                    [21]                                   |\n"
             "|      Scenario 2.2                    [22]                                   |\n"
             "|      Scenario 2.3                    [23]                                   |\n"
             "|      Scenario 2.4                    [24]                                   |\n"
             "|      Scenario 2.5                    [25]                                   |\n"
             "|      Exit                            [0]                                   |\n"
             "|============================================================================|\n";

        cout << endl;
        cout << "Choose an option: ";
        int choice;

        cin >> choice;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input!" << endl;
            continue;
        }
        if(choice == 0) {exit(0);}
        cout << "Please input the following values:";
        cout << "Graph (1 - 10): " ;
        int gindex;
        cin >> gindex;
        Graph g1(gindex);

        int start;
        int end;
        int given;
        int units;
        int dummy;

        switch (choice)
        {
            case 11:
                cout << "Starting stop (index): ";
                cin >> start;
                cout << "Ending stop (index): " ;
                cin >> end;
                given = g1.maximumCapacityWays(start, end);
                cout << "The max size is " << given << endl;
                g1.bfsprint(start,given);
                break;
            case 12:
                cout << "Starting stop (index): ";
                cin >> start;
                cout << "Ending stop (index): " ;
                cin >> end;
                given = g1.maximumCapacityWays(start, end);
                cout << "The max size is " << given << endl;
                g1.bfsprint(start,given);
                given = g1.minimumTransshipments(start, end);
                g1.bfsprint(start,given);
                break;

            case 21:
                cout << "Starting stop (index): ";
                cin >> start;
                cout << "Ending stop (index): " ;
                cin >> end;
                cout << "Group size: " ;
                cin >> given;
                g1.fordFulkerson(start, end, given);
                break;
            case 22:
                cout << "Starting stop (index): ";
                cin >> start;
                cout << "Ending stop (index): " ;
                cin >> end;
                cout << "Group size: " ;
                cin >> given;
                cout << "Units to increase: " ;
                cin >> units;
                cout << "Previous path: " << endl;
                g1.fordFulkerson(start, end, given);
                cout << "Corrected path: " << endl;
                g1.fordFulkersonNonZeroFlow(start, end, units);
                break;
            case 23:
                cout << "Starting stop (index): ";
                cin >> start;
                cout << "Ending stop (index): " ;
                cin >> end;
                dummy = g1.fordFulkerson(start, end);
                cout << "Max size: " << dummy << endl;
                break;
            case 24:
                cout << "Starting stop (index): ";
                cin >> start;
                cout << "Ending stop (index): " ;
                cin >> end;
                cout << "Group size: " ;
                cin >> given;
                cout << "Units to increase: " ;
                cin >> units;
                cout << "Previous path: " << endl;
                g1.fordFulkerson(start, end, given);
                cout << "Corrected path: " << endl;
                g1.fordFulkersonNonZeroFlow(start, end, units);
                break;
            case 25:
                cout << "Starting stop (index): ";
                cin >> start;
                cout << "Ending stop (index): " ;
                cin >> end;
                cout << "Group size: " ;
                cin >> given;
                cout << "Units to increase: " ;
                cin >> units;
                cout << "Previous path: " << endl;
                g1.fordFulkerson(start, end, given);
                cout << "Corrected path: " << endl;
                g1.fordFulkersonNonZeroFlow(start, end, units);
                break;
        }
    }
}

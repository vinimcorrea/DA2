//
// Created by Vinícius Correa on 17/05/2022.
//

#ifndef SECOND_PROJECT_VEHICLE_H
#define SECOND_PROJECT_VEHICLE_H


class Vehicle {
    int departure;
    int arrival;
    int capacity;
    int time;

public:
    Vehicle(int departure, int arrival, int capacity, int time);

    int getDeparture() const;

    int getArrival() const;

    int getCapacity() const;

    int getTime() const;
};


#endif //SECOND_PROJECT_VEHICLE_H

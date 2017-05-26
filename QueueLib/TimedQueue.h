//
// Created by Juscelino Tanaka on 15/05/17.
//

#include <vector>
#include <iostream>


#ifndef QUEUES_TIMEDQUEUE_H
#define QUEUES_TIMEDQUEUE_H

using namespace std;

class Element {
public:
    int id;
    int serverId;
    double arrivalTime;
    double startTime;
    double endTime;
    double operationDuration;
    double waitTime;
    double totalTime;

    void SetStartTime(double startTime);
};

class Server {
public:
    int id;
    double nextAvailableTime;

    Server(int i) {
        this->id = i;
        this->nextAvailableTime = 0;
    }

    Server() {
        this->id = 0;
        this->nextAvailableTime = 0;
    }

    int totalExecuted;
};

class TimedQueue{
public:

    TimedQueue();

    void AddElement(int id, float arrivalTime, float operationDuration);
    void ProcessQueue();
    double Size();
    double WaitingAverage();
    Server s;

private:
//    vector<Element> element;
    double waitAvg;
    double totalWaitTime;
    int totalElements;
};

#endif //QUEUES_TIMEDQUEUE_H

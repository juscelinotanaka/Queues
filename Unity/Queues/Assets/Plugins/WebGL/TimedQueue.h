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

class TimedQueue{
public:

    TimedQueue();

    void AddElement(int id, float arrivalTime, float operationDuration);
    void ProcessQueue();

    Element &operator[] (int index);
    Element operator[] (int index) const;

    double Size();
    double WaitingAverage();
    void ListQueue();

private:
    vector<Element> element;
    double waitAvg;
    double totalWaitTime;
};

#endif //QUEUES_TIMEDQUEUE_H

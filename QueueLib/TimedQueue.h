//
// Created by Juscelino Tanaka on 15/05/17.
//

typedef void (* LogCallback) (const char * objectName);

#include <vector>

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
    double Average();
    void ListQueue(LogCallback logCallback);

private:
    vector<Element> element;
    double AVG;
    double totalTime;
};

#endif //QUEUES_TIMEDQUEUE_H

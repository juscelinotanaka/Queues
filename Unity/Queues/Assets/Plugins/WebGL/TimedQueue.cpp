//
// Created by Juscelino Tanaka on 15/05/17.
//

#include "TimedQueue.h"

void TimedQueue::AddElement(int id, float arrivalTime, float operationDuration) {
    Element e;
    e.id = id;
    e.startTime = 0;
    e.endTime = 0;
    e.waitTime = 0;
    e.arrivalTime = arrivalTime;
    e.operationDuration = operationDuration;

    if (s.nextAvailableTime <= e.arrivalTime) {
        e.SetStartTime(e.arrivalTime);
        s.nextAvailableTime = e.arrivalTime + e.operationDuration;
    } else {
        e.SetStartTime(s.nextAvailableTime);
        s.nextAvailableTime += e.operationDuration;
    }
    e.serverId = s.id;
    s.totalExecuted++;

    totalWaitTime += e.waitTime;
    totalElements++;
}

TimedQueue::TimedQueue() {
    s = Server(0);
    totalElements = 0;
    totalWaitTime = 0;
}

void TimedQueue::ProcessQueue() {
    waitAvg = totalWaitTime / Size();
}

double TimedQueue::Size() {
    return totalElements;
}

double TimedQueue::WaitingAverage() {
    return waitAvg;
}

void Element::SetStartTime(double startTime) {
    this->startTime = startTime;
    this->endTime = startTime + operationDuration;
    this->waitTime = startTime - arrivalTime;
    this->totalTime = endTime - arrivalTime;
}

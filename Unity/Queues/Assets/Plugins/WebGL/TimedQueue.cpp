//
// Created by Juscelino Tanaka on 15/05/17.
//

#include "TimedQueue.h"

//mutator operator[] ---> used to change data members;
Element& TimedQueue::operator[](int index)
{
    if (index < 0 || index > element.size())
        throw out_of_range("Index out of range");

    return element[index];
}

//Accessor operator[]---> used to read data members
Element TimedQueue::operator[](int index) const
{
    if (index < 0 || index > element.size())
        throw out_of_range("Index out of range");

    return element[index];
}

void TimedQueue::AddElement(int id, float arrivalTime, float operationDuration) {
    Element e;
    e.id = id;
    e.startTime = 0;
    e.endTime = 0;
    e.waitTime = 0;
    e.arrivalTime = arrivalTime;
    e.operationDuration = operationDuration;

    element.push_back(e);
}

TimedQueue::TimedQueue() {
}

void TimedQueue::ProcessQueue() {
    totalWaitTime = 0;

    for (int i = 0; i < element.size(); ++i) {
        Element e = element[i];

        totalWaitTime += e.waitTime;
    }
    waitAvg = totalWaitTime / Size();
}

double TimedQueue::Size() {
    return element.size();
}

double TimedQueue::WaitingAverage() {
    return waitAvg;
}

void TimedQueue::ListQueue() {
    for (int i = 0; i < element.size(); ++i) {
        char * str;
        Element e = element[i];
        printf("e[%3d] arrival: %3.8f\t\t"
                       "start: %3.8f\t\t"
                       "wait: %3.8f\t\t"
                       "end: %3.8f\t\t"
                       "operationDuration: %3.8f\t\t"
                       "total: %3.8f\t\t"
                       "server: %d\n",
               e.id, e.arrivalTime, e.startTime, e.waitTime, e.endTime,
               e.operationDuration, e.totalTime, e.serverId );
    }
}

void Element::SetStartTime(double startTime) {
    this->startTime = startTime;
    this->endTime = startTime + operationDuration;
    this->waitTime = startTime - arrivalTime;
    this->totalTime = endTime - arrivalTime;
}

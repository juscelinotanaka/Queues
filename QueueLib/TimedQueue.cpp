//
// Created by Juscelino Tanaka on 15/05/17.
//

#include "TimedQueue.h"

// mutator operator[] ---> used to change data members;
// [PT] usado somente para acessar um item diretamente com o operador []. Igual array.
Element& TimedQueue::operator[](int index)
{
    if (index < 0 || index > element.size())
        throw out_of_range("Index out of range");

    return element[index];
}

//Accessor operator[]---> used to read data members
// [PT] mesma coisa aqui, só que apenas para leitura.
Element TimedQueue::operator[](int index) const
{
    if (index < 0 || index > element.size())
        throw out_of_range("Index out of range");

    return element[index];
}

// add an element.
// [PT] Ao adicionar um elemento precisamos saber a hora que ele chegou (arrivalTime) e
// quanto tempo ele vai passar (operationDuration). O restante das informações serão atualizadas quando um server
// chamar ele para ser atendido. So ai saberemos quanto tempo ele esperou, etc.
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

// calculates the total waiting time and divides by the total of elements on queue = avg waiting time.
// [PT] a soma de todos os tempos esperados por cada elemento dividido pelo total de elementos nos dará a média de
// espera total de todos os elementos que foram atendidos.
void TimedQueue::ProcessQueue() {
    totalWaitTime = 0;

    for (int i = 0; i < element.size(); ++i) {
        Element e = element[i];

        totalWaitTime += e.waitTime;
    }
    waitAvg = totalWaitTime / Size();
}

// total elements on queue
double TimedQueue::Size() {
    return element.size();
}

// return the calculated value on ProcessQueue. Which means, if you don't call that function this will return 0;
double TimedQueue::WaitingAverage() {
    return waitAvg;
}

// list each element with its information. This can take so long for huge lists (i.e. 10^7).
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

// set the start time of an element - from here we can calculate other related stuffs
// [PT] quando calculamos o tempo de início (não confunda com tempo de chegada - arrivalTime) nós podemos calcular
// outras informações, pois o tempo de operação já é conhecido (foi calculado um tempo aleatório lá no addElement).
// Com isso e o horário real de início (que foi a hora que o server chamou o elemento pra ser atendido) a gente sabe
// quanto ele esperou desde a chegada (waitTime) e o tempo total gasto desde a chegada até a saída (totalTime).
void Element::SetStartTime(double startTime) {
    this->startTime = startTime;
    this->endTime = startTime + operationDuration;
    this->waitTime = startTime - arrivalTime;
    this->totalTime = endTime - arrivalTime;
}

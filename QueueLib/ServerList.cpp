//
// Created by Juscelino Tanaka on 21/05/17.
//

#include "ServerList.h"

ServerList::ServerList(int totalServers) {
    if (totalServers <= 0)
        totalServers = 1;

    for (int i = 0; i < totalServers; ++i) {
        Server s(i);
        servers.push_back(s);
    }
}

Server * ServerList::GetFirstAvailable(double arrivalTime) {
    Server * min = &servers[0];

    for (int i = 1; i < servers.size(); ++i) {
        if (min->nextAvailableTime < arrivalTime)
            return min;

        if (servers[i].nextAvailableTime < min->nextAvailableTime)
            min = &servers[i];
    }

    return min;
}

Server *ServerList::GetLessTired() {
    Server * min = &servers[0];

    for (int i = 1; i < servers.size(); ++i) {
        if (servers[i].nextAvailableTime < min->nextAvailableTime)
            min = &servers[i];
    }

    return min;
}

void ServerList::RunQueue(TimedQueue * queue) {

    for (int i = 0; i < queue->Size(); ++i) {
        Element &e = queue[0][i];
        Server * s = GetFirstAvailable(e.arrivalTime);
//        Server * s = GetLessTired();

        if (s->nextAvailableTime < e.arrivalTime) {
            e.SetStartTime(e.arrivalTime);
            s->nextAvailableTime = e.arrivalTime + e.operationDuration;
        } else {
            e.SetStartTime(s->nextAvailableTime);
            s->nextAvailableTime += e.operationDuration;
        }
        e.serverId = s->id;
        s->totalExecuted++;
    }
}
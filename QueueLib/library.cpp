#include "library.h"
#include "TimedQueue.h"
#include "ServerList.h"
#include "mt.h"
#include <cmath>

static UnityCommandCallback lastCallback = NULL;

void Log(const char * string);

void ConnectCallback(UnityCommandCallback callbackMethod) {
    lastCallback = callbackMethod;
}

void CallMethod(const char * commandName, const char * commandData){
    if (lastCallback != NULL)
        lastCallback(commandName, commandData);
}

void RegisterLogger(LogCallback l) {
    logger = l;
}

double ExponentialRandom(double seed, double lambda) {
    return -log(seed) / lambda;
}

double ExecMM1(int exponent, float interArrivalMean, float serviceRateMean, int servers, bool listQueue) {

    Log("starting");

    TimedQueue queue;
    ServerList server(servers);

    int sampleSize = pow(10, exponent);

    vector<double> interArrivalTime;
    vector<double> serviceTime;

    MersenneTwister mt;

    Log("creating random interval arrival times");

    // generate arrive intervals
    for (int i = 0; i < sampleSize; ++i) {
        double seed = mt.genrand_real2();
        double random = ExponentialRandom(seed, interArrivalMean);
        interArrivalTime.push_back(random);
    }

    Log("creating random service times");

    // generate execution operationDuration
    for (int i = 0; i < sampleSize; ++i) {
        double seed = mt.genrand_real2();
        serviceTime.push_back(ExponentialRandom(seed, serviceRateMean));
    }

    Log("adding elements to queue");

    double arrivalTime = 0;

    // create queue with all elements
    for (int i = 0; i < sampleSize; ++i) {
        arrivalTime += interArrivalTime[i];
        queue.AddElement(i, arrivalTime, serviceTime[i]);
    }

    Log("Running queue on servers.");

    server.RunQueue(&queue);

    Log("Calculating queue times.");

    queue.ProcessQueue();

    if (listQueue) {
        Log("Listing queue:");
        queue.ListQueue(logger);
    }

    return queue.Average();
}


void Log(const char *string) {
    logger(string);
}

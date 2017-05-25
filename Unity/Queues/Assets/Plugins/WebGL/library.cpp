#include "library.h"
#include "TimedQueue.h"
#include "ServerList.h"

using namespace std;

MersenneTwister mt;

void Hello ()
{
    printf("Hello, world!\n");
}

void Log(const char * str) {
    cout << str << endl;
}

double ExponentialRandom(double seed, double lambda) {
    return -log(seed) / lambda;
}

double ExecMM1(int exponent, float interArrivalMean, float serviceRateMean, int servers, bool listQueue) {

    Log("starting");

    TimedQueue queue;
    ServerList server(servers);

    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();

    mt.init_genrand(seed1);

    int sampleSize = pow(10, exponent);

    double interArrivalTime;
    double serviceTime;

    string s = "creating random interval arrival times for a sampling of " + to_string(sampleSize) + " elements.";

    Log(s.c_str());

    double arrivalTime = 0;

    // create queue with all elements
    for (int i = 0; i < sampleSize; ++i) {
        double seed = mt.genrand_real2();
        interArrivalTime = ExponentialRandom(seed, interArrivalMean);

        seed = mt.genrand_real2();
        serviceTime = ExponentialRandom(seed, serviceRateMean);

        arrivalTime += interArrivalTime;
        queue.AddElement(i, arrivalTime, serviceTime);
    }

    Log("Running queue on servers.");

    server.RunQueue(&queue);

    Log("Calculating queue times.");

    queue.ProcessQueue();

    if (listQueue) {
        Log("Listing queue:");
        queue.ListQueue();
    }

    return queue.WaitingAverage();
}

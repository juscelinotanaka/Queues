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

    // we need to generate a random number to make the MersenneTwister be different everytime it starts.
    // Read more about it on MersenneTwister documentation.
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
        // random seeds will be used to generate exponential random number - which means M from "M"/M/1
        double seed = mt.genrand_real2();
        interArrivalTime = ExponentialRandom(seed, interArrivalMean);

        seed = mt.genrand_real2();
        serviceTime = ExponentialRandom(seed, serviceRateMean); // here is the 2nd M - M/"M"/1

        // the sum of inter arrival times will be giving the real arriving time of each element.
        // ex.: if first interval is 1 - arriving[0] = 1.
        // if next interval = 0.5 -> arriving[1] = 1+0.5 = 1.5.
        // if next = .75 arr[2] = 1 + 0.5 + .75 = 2.25....
        arrivalTime += interArrivalTime;
        queue.AddElement(i, arrivalTime, serviceTime);
    }

    Log("Running queue on servers.");

    // after we add all process to the queue then we can run the queue on a list of server - in this case 1 (M/M/"1")
    server.RunQueue(&queue);

    Log("Calculating queue times.");

    // after all process pass in a server we need to get their waiting average. It will be calculate here:
    queue.ProcessQueue();

    // this is not necessary and you should never set it to true unless you want to wait forever for 10^7.
    // Writing in console is so expensive compared to just math only.
    if (listQueue) {
        Log("Listing queue:");
        queue.ListQueue();
    }

    // the we return the processed waiting average time.
    return queue.WaitingAverage();
}

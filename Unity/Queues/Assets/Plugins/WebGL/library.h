#include "mt.h"
#include <iostream>
#include <cmath>

extern "C" {
    void Hello ();
    void Log(const char * str);
    double ExecMM1(int exponent, float interArrivalMean, float serviceRateMean, int servers, bool listQueue);
}
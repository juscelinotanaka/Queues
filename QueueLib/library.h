typedef void (* UnityCommandCallback) (const char * commandName, const char * commandData);
typedef void (* LogCallback) (const char * objectName);

static LogCallback logger;



extern "C" {

    void RegisterLogger(LogCallback l);

    void ConnectCallback(UnityCommandCallback callbackMethod);
    void CallMethod(const char *commandName, const char *commandData);

    double ExecMM1(int exponent, float interArrivalMean, float serviceRateMean, int servers, bool listQueue);
}
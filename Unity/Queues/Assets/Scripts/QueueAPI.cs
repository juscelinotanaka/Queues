using UnityEngine;
using System.Runtime.InteropServices;

public class QueueAPI
{
    public delegate void StringCallbackDelegate( string s );
    public delegate void UnityCommandCallback( string command, string data );
    private static GameObject CallbackObject;

    [DllImport("QueueLib")]
    private static extern void RegisterLogger(StringCallbackDelegate callback);

    [DllImport("QueueLib")]
    private static extern void ConnectCallback(UnityCommandCallback callback);

    [DllImport("QueueLib")]
    private static extern double ExecMM1(int exponent, double interArrivalMean, double serviceRateMean, int servers,
        bool listQueue);

    public static void InitAPI(GameObject callbackObject)
    {
        CallbackObject = callbackObject;
        RegisterLogger(Logger);
        ConnectCallback(ReceiveCallback);
    }

    public static double RunMM1(int exponent, double interArrivalMean, double serviceRateMean, int servers = 1,
        bool listQueue = false)
    {
        return ExecMM1(exponent, interArrivalMean, serviceRateMean, servers, listQueue);
    }

    private static void ReceiveCallback(string command, string data)
    {
        CallbackObject.SendMessage(command, data);
    }

    static void Logger(string msg)
    {
        CallbackObject.SendMessage("Log", msg);
    }
}
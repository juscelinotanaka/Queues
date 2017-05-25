using System;
using UnityEngine;
using System.Runtime.InteropServices;
using Random = UnityEngine.Random;

public class QueueAPI
{

#if UNITY_EDITOR

    private static double ExecMM1(int exponent, float interArrivalMean, float serviceRateMean, int servers,
        bool listQueue)
    {
        return interArrivalMean/serviceRateMean < 0.9f ? 0 : Random.Range(interArrivalMean/100f, serviceRateMean/100f);
    }
#elif UNITY_WEBGL
    [DllImport("__Internal")]
    private static extern double ExecMM1(int exponent, float interArrivalMean, float serviceRateMean, int servers,
        bool listQueue);
#endif


#if UNITY_EDITOR

#elif UNITY_WEBGL
    [DllImport("__Internal")]
#endif
    private static extern void Hello();

#if UNITY_EDITOR

#elif UNITY_WEBGL
    [DllImport("__Internal")]
#endif
    private static extern void Log(string str);


    public static void InitAPI(GameObject callbackObject)
    {
#if !UNITY_EDITOR
        Application.logMessageReceived += ApplicationOnLogMessageReceived;
#endif

        Console.Log("API is Ready.");
    }

    private static void ApplicationOnLogMessageReceived(string logString, string stackTrace, LogType type)
    {
        Console.Log(logString);
    }

    public static double RunMM1(int exponent, float interArrivalMean, float serviceRateMean, int servers = 1,
        bool listQueue = false)
    {
        return ExecMM1(exponent, interArrivalMean, serviceRateMean, servers, listQueue);
    }
}
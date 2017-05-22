using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Manager : MonoBehaviour
{

    public int pot, server;
    public float interArrivalMean, serviceRateMean;
    public bool listQueue;

    void Awake()
    {
        QueueAPI.InitAPI(gameObject);
    }

    // Use this for initialization
    void Start()
    {
        double val = QueueAPI.RunMM1(pot, interArrivalMean, serviceRateMean, listQueue: listQueue);
        Console.Log("val : " + val);
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void InternalLog(string msg)
    {

    }

    public void Log(string msg)
    {
        Debug.Log(msg);
        Console.Log(msg);
    }
}
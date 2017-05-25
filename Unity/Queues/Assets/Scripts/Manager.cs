using UnityEngine;
using UnityEngine.UI;

public class Manager : MonoBehaviour
{

    public InputField minPotInput;
    public InputField plusInput;
    public InputField interArrivalMeanInput;
    public InputField serviceRateInput;
    public InputField serversInput;
    public Text serverUsage;

    public int minPot = 3, plusCases = 3;
    public int servers = 1;
    public float interArrivalMean, serviceRateMean;
    public bool listQueue;

    void Awake()
    {
        QueueAPI.InitAPI(gameObject);

        minPotInput.onEndEdit.AddListener(TryParseValues);
        plusInput.onEndEdit.AddListener(TryParseValues);
        interArrivalMeanInput.onEndEdit.AddListener(TryParseValues);
        serviceRateInput.onEndEdit.AddListener(TryParseValues);
        serversInput.onEndEdit.AddListener(TryParseValues);
    }

    public void TryParseValues(string s = "")
    {
        try
        {
            int.TryParse(minPotInput.text, out minPot);
            int.TryParse(plusInput.text, out plusCases);
            int.TryParse(serversInput.text, out servers);
            float.TryParse(interArrivalMeanInput.text, out interArrivalMean);
            float.TryParse(serviceRateInput.text, out serviceRateMean);

            serverUsage.text = string.Format("Server Usage: {0:0.0}%", (interArrivalMean / serviceRateMean) * 100);
        }
        catch
        {
            Console.Log("Some attribute is wrong. Please fix it!");
            throw;
        }
    }

    public void RunTest()
    {
        Graph.Instance.Clear();
        TryParseValues();

        for (int i = minPot; i <= Mathf.Min(7, minPot + plusCases); i++)
        {
            RequestQueue(i);
        }

        Graph.Instance.Plot();
    }

    void RequestQueue(int pot)
    {
        Console.Log("Requesting for 10^" + pot);
        double val = QueueAPI.RunMM1(pot, interArrivalMean, serviceRateMean, servers, listQueue);
        Graph.Instance.AddPoint("10^" + pot, (float) val);
        Console.Log("10^" + pot + ": " + val);
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
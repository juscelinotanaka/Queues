using UnityEngine;
using UnityEngine.UI;

public class Console : MonoBehaviour
{
    private static Console i;

    public RectTransform contentArea;
    public GameObject[] linePrefab;


    void Awake()
    {
        i = this;
    }

    public static void Log(string msg)
    {
        GameObject line = Instantiate(i.linePrefab[i.contentArea.childCount % i.linePrefab.Length], i.contentArea);
        line.transform.GetChild(0).GetComponent<Text>().text = msg;
    }
}

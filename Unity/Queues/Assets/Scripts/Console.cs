using UnityEngine;
using UnityEngine.UI;

public class Console : MonoBehaviour
{
    private static Console i;

    public RectTransform contentArea;
    public GameObject[] linePrefab;
    public ScrollRect scroll;

    private bool alwaysOnBottom = true;

    public bool AlwaysOnBottom
    {
        get { return alwaysOnBottom; }
        set { alwaysOnBottom = value; }
    }

    void Awake()
    {
        i = this;
        scroll = GetComponent<ScrollRect>();
    }

    public static void Log(string msg)
    {
        GameObject line = Instantiate(i.linePrefab[i.contentArea.childCount % i.linePrefab.Length], i.contentArea);
        line.transform.GetChild(0).GetComponent<Text>().text = msg;

        if (i.alwaysOnBottom)
        {
            Canvas.ForceUpdateCanvases();
            i.scroll.verticalNormalizedPosition = 0f;
        }
    }

    public void ClearAll()
    {
        int count = contentArea.childCount;

        for (int i = 0; i < count; i++)
        {
            Destroy(contentArea.GetChild(i).gameObject);
        }
        scroll.verticalNormalizedPosition = 1f;
    }
}

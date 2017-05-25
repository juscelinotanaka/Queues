using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.UI.Extensions;

public class PointData
{
    public string data;
    public float value;

    public PointData(string data, float value)
    {
        this.data = data;
        this.value = value;
    }
}

public class Graph : MonoBehaviour
{
    public static Graph Instance;
    public RectTransform verticalLine, horizontalLine;
    private RectTransform rectTransform;
    public GameObject verticalTextPrefab, horizontalTextPrefab;
    public UILineRenderer line;
    public InputField minInput, maxInput;

    public float marginLeft = 50, marginRight = 30, marginTop = 30, marginBottom = 30;
    public List<PointData> points = new List<PointData>();
    public List<float> existingValues = new List<float>();

    public float width, height;

    public float min, max;
    
    
    
    // Use this for initialization
    void Awake()
    {
        Instance = this;
        rectTransform = transform as RectTransform;
        minInput.onEndEdit.AddListener(SetMinValue);
        maxInput.onEndEdit.AddListener(SetMaxValue);
        SetMinValue(minInput.text);
        SetMaxValue(maxInput.text);
    }

    private void SetMinValue(string arg0)
    {
        float val = 0;
        float.TryParse(arg0, out val);

        minInput.text = val.ToString("F2");
        
        min = val;
    }
    
    private void SetMaxValue(string arg0)
    {
        float val = 1;
        float.TryParse(arg0, out val);

        maxInput.text = val.ToString("F2");
        
        max = val;
    }

    void Mock()
    {
        points.Clear();
        AddPoint("10^3", 0.1f);
        AddPoint("10^4", 0.12f);
        AddPoint("10^5", 0.333f);
        AddPoint("10^6", 0.22f);
        AddPoint("10^7", 0.22f);
        AddPoint("10^7", 0.22f);
    }

    public void AddPoint(string data, float value)
    {
        points.Add(new PointData(data, value));
    }

    void OnValidate()
    {
        rectTransform = transform as RectTransform;
        
        verticalLine.anchoredPosition = Vector2.right * marginLeft;
        horizontalLine.anchoredPosition = Vector2.up * marginBottom;
    }

    public void Plot()
    {
        width = rectTransform.rect.width - marginLeft - marginRight;
        height = rectTransform.rect.height - marginBottom - marginTop;
        var total = points.Count;
        var horizontalSpacing = width / total;
        
        line.Points = new Vector2[total];
        
        for (int i = 0; i < total; i++)
        {
            var val = points[i].value;
            var verticalPos = marginBottom + height * Mathf.InverseLerp(min, max, val);
            if (!existingValues.Contains(val))
            {
                existingValues.Add(val);
                
                var v = Instantiate(verticalTextPrefab, verticalLine).GetComponent<Text>();
                v.text = val.ToString("F4");
                v.rectTransform.anchoredPosition = Vector2.up * (verticalPos - verticalLine.rect.height / 2);
            }
            
            var h = Instantiate(horizontalTextPrefab, horizontalLine).GetComponent<Text>();
            h.text = points[i].data;
            h.rectTransform.anchoredPosition = Vector2.right * (marginLeft + i * horizontalSpacing);
            
            line.Points[i] = new Vector2(marginLeft + i * horizontalSpacing, verticalPos);
        }
    }

    public void RePlot()
    {
        for (int i = 0; i < verticalLine.childCount; i++)
        {
            Destroy(verticalLine.GetChild(i).gameObject);
        }
        for (int i = 0; i < horizontalLine.childCount; i++)
        {
            Destroy(horizontalLine.GetChild(i).gameObject);
        }
        existingValues.Clear();
        SetMinValue(minInput.text);
        SetMaxValue(maxInput.text);
        Plot();
    }

    public void Clear()
    {
        points.Clear();
        existingValues.Clear();
        for (int i = 0; i < verticalLine.childCount; i++)
        {
            Destroy(verticalLine.GetChild(i).gameObject);
        }
        for (int i = 0; i < horizontalLine.childCount; i++)
        {
            Destroy(horizontalLine.GetChild(i).gameObject);
        }
    }
}

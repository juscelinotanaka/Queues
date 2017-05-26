﻿using System;
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
    
    private List<GameObject> verticalTexts = new List<GameObject>();
    [SerializeField] private RectTransform rectTransform;
    
    public RectTransform verticalLine;
    public RectTransform horizontalLine;
    public RectTransform AvgLine;
    public Text avgText;
    public GameObject verticalTextPrefab;
    public GameObject horizontalTextPrefab;
    public UILineRenderer line;
    public InputField minInput;
    public InputField maxInput;
    public InputField offsetMinInput;
    public InputField offsetMaxInput;
    public InputField avgInput;

    public Toggle minMaxToggle;

    private bool autoMinMax = false;
    public bool AutoMinMax
    {
        get { return autoMinMax; }
        set { autoMinMax = value; }
    }

    public float marginLeft = 50, marginRight = 30, marginTop = 30, marginBottom = 30;
    public List<PointData> points = new List<PointData>();
    public List<float> existingValues = new List<float>();

    public float width, height;

    private float min, max;
    public float Min
    {
        get { return min - offsetMin; }
        set { min = value; }
    }

    public float Max
    {
        get { return max + offsetMax; }
        set { max = value; }
    }
    private float offsetMin;
    private float offsetMax;

    void OnValidate()
    {
//        rectTransform = transform as RectTransform;
        
        verticalLine.anchoredPosition = Vector2.right * marginLeft;
        horizontalLine.anchoredPosition = Vector2.up * marginBottom;
    }
    
    // Use this for initialization
    void Awake()
    {
        Instance = this;
//        rectTransform = transform as RectTransform;
        minInput.onEndEdit.AddListener(SetMinValue);
        maxInput.onEndEdit.AddListener(SetMaxValue);
        offsetMinInput.onEndEdit.AddListener(SetOffsetMin);
        offsetMaxInput.onEndEdit.AddListener(SetOffsetMax);
        avgInput.onEndEdit.AddListener(SetAvgPosition);
//        avgInput.onValueChanged.AddListener(AutoSetAvg);
        minMaxToggle.onValueChanged.AddListener(SetMinMax);
        SetMinValue(minInput.text);
        SetMaxValue(maxInput.text);
        SetAvgPosition(avgInput.text);
        SetOffsetMin(offsetMinInput.text);
        SetOffsetMax(offsetMaxInput.text);
        SetMinMax(minMaxToggle.isOn);
    }

    private void SetOffsetMax(string arg0)
    {
        float val = 0;
        float.TryParse(arg0, out val);

        offsetMaxInput.text = val.ToString("F3");

        offsetMax = val;

        RePlot(true);
    }

    private void SetOffsetMin(string arg0)
    {
        float val = 0;
        float.TryParse(arg0, out val);

        offsetMinInput.text = val.ToString("F3");
        
        offsetMin = val;
        
        RePlot(true);
    }

    public void AddPoint(string data, float value)
    {
        if (autoMinMax)
        {
            if (value < min)
            {
                min = value;
                minInput.text = min.ToString("F3");
            }
            if (value > max)
            {
                max = value;
                maxInput.text = max.ToString("F3");
            }
        }
        points.Add(new PointData(data, value));
    }
    
    public void Plot()
    {
        width = rectTransform.rect.width - marginLeft - marginRight;
        height = rectTransform.rect.height - marginBottom - marginTop;
        var total = points.Count;
        var horizontalSpacing = width / total;
        
        line.Points = new Vector2[total];
        
//        SetAvgPosition(avgInput.text);
        
        for (int i = 0; i < total; i++)
        {
            var val = points[i].value;
            var verticalPos = marginBottom + height * Mathf.InverseLerp(Min, Max, val);
            var horizontalPos = marginLeft + i * horizontalSpacing;
            if (!existingValues.Contains(val))
            {
                existingValues.Add(val);
                
                var v = Instantiate(verticalTextPrefab, rectTransform).GetComponent<Text>();
                verticalTexts.Add(v.gameObject);
                v.text = val.ToString("F4");
                v.rectTransform.anchoredPosition = new Vector2(horizontalPos, verticalPos);
            }
            
            var h = Instantiate(horizontalTextPrefab, horizontalLine).GetComponent<Text>();
            h.text = points[i].data;
            h.rectTransform.anchoredPosition = Vector2.right * (marginLeft + i * horizontalSpacing);
            
            line.Points[i] = new Vector2(horizontalPos, verticalPos);
        }
    }

    public void RePlot(bool skipMinMax = false)
    {
        for (int i = 0; i < verticalTexts.Count; i++)
        {
            Destroy(verticalTexts[i]);
        }
        verticalTexts.Clear();
        for (int i = 0; i < horizontalLine.childCount; i++)
        {
            Destroy(horizontalLine.GetChild(i).gameObject);
        }
        existingValues.Clear();
        if (!skipMinMax)
        {
            SetMinValue(minInput.text);
            SetMaxValue(maxInput.text);
        }
        SetAvgPosition(avgInput.text);
        Plot();
    }
    
    public void Clear()
    {
        points.Clear();
        if (autoMinMax)
        {
            Min = 99999;
            Max = -99999;
        }
        existingValues.Clear();
        for (int i = 0; i < verticalTexts.Count; i++)
        {
            Destroy(verticalTexts[i]);
        }
        verticalTexts.Clear();
        for (int i = 0; i < horizontalLine.childCount; i++)
        {
            Destroy(horizontalLine.GetChild(i).gameObject);
        }
    }

    public void SetAvg(float avg)
    {
        SetAvgPosition(avg.ToString("F3"));
    }

    private void SetMinMax(bool status)
    {
        minInput.interactable = !status;
        maxInput.interactable = !status;

        autoMinMax = status;

        if (status)
        {
            Min = 99999;
            Max = -99999;
        }
    }

    private void SetMinValue(string arg0)
    {
        float val = 0;
        float.TryParse(arg0, out val);

        minInput.text = val.ToString("F3");
        
        Min = val;
        
        RePlot(true);
    }
    
    private void SetMaxValue(string arg0)
    {
        float val = 1;
        float.TryParse(arg0, out val);

        maxInput.text = val.ToString("F3");
        
        Max = val;
        
        RePlot(true);
    }

    private void SetAvgPosition(string arg0)
    {
        float val = 0;

        float.TryParse(arg0, out val);
        
//        Debug.Log("min: " + Min + " : " + Max + " : " + val);
//        Debug.Log("ilerp: " + Mathf.InverseLerp(Min, Max, val));
        
        var verticalPos = marginBottom + height * Mathf.InverseLerp(Min, Max, val);

        AvgLine.anchoredPosition = Vector2.up * verticalPos;
        
        avgText.text = val.ToString("F3");
        avgInput.text = avgText.text;
    }

    
}

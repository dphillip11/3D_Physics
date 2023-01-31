using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChangeColor : MonoBehaviour
{
    public static Color[] colors =
    {
        Color.cyan, Color.magenta, Color.red,Color.yellow, Color.blue,Color.green
    };
    private Material material;
    private int colorID = 0;
    public void Start()
    {
        material= GetComponent<Renderer>().material;
    }


    private void OnCollisionEnter(UnityEngine.Collision collision)
    {
        colorID = (colorID + 1) % 6;
        material.color= colors[colorID];
    }
}

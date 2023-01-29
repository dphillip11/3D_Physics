using System.Collections;
using System.Collections.Generic;
using UnityEngine;

interface ShapeInterface
{       
    public string getType();
    public void c_Start();
}
public abstract class ShapeComponent : MonoBehaviour, ShapeInterface
{
    protected string type = "empty";
    public int shapeIdentifier;
    public PointMass body;

    public void Start()
    {
        body = GetComponent<PointMass>();
        c_Start();
        ShapeManager.AddShape(this);
    }
    public abstract string getType();

    public abstract void c_Start();
}

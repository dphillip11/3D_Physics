using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class SphereComponent : ShapeComponent
{
    public float radius;
    public Material material;
    public override void c_Start()
    {
        type = "sphere";
        radius = 0.5f * transform.localScale.x;
    }

    public override string getType()
    {
        return type;
    }
}

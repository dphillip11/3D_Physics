using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class PlaneComponent : ShapeComponent
{
    public float m_width;
    public float m_depth;

    // Start is called before the first frame update
    public override void c_Start()
    {
        type = "plane";
        m_width = transform.localScale.x * 10;
        m_depth = transform.localScale.y * 10;
    }

    public override string getType()
    {
        return type;
    }
}

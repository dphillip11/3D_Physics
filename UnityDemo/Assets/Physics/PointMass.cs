using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PointMass : MonoBehaviour
{
    public Vector3 centre;
    public Vector3 velocity = Vector3.zero;
    public Vector3 acceleration = Vector3.zero;
    public bool isStatic = true;
    public float linearDrag = 0.1f;
    public float mass;
    public float restitution = 1;
    public ShapeComponent shape;

    public void Start()
    {
        shape = GetComponent<ShapeComponent>();
        if (shape == null)
            Debug.Log("No shape when instantiating body");
        centre = transform.position;
        PhysicsManager.AddBody(this);
    }
}

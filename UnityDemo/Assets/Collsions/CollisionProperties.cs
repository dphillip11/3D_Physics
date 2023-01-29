using UnityEngine;

public struct Collision
{
    public bool isActive;
    public bool isResolved;
    public Vector3 position;
    public Vector3 normal;
    //shape identifier
    public int collider0;
    public int collider1;
};

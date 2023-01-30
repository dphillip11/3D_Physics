using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq.Expressions;
using Unity.Collections;
using UnityEngine;

public class DataManager
{
    //initial alocation size
    public int initialSize = 2000;
    public int currentCapacity = 2000;
    public int ballCount = 0;

    // ball components
    public NativeArray<bool> isStatic;
    public NativeArray<Vector3> position;
    public NativeArray<Vector3> velocity;
    public NativeArray<float> radius;
    public NativeArray<float> linearDrag;
    public NativeArray<float> mass;
    public NativeArray<float> restitution;
    // collisions
    public NativeArray<Collision> collisions;
    //in game ball transforms
    public Transform[] bTransforms;
    public Material[] ballMaterials;
    public Color[] colors =
    {
        Color.cyan, Color.magenta, Color.red,Color.yellow, Color.blue,Color.green
    };

    public void Init()
    {
        isStatic = new NativeArray<bool>(initialSize, Allocator.Persistent);
        position = new NativeArray<Vector3>(initialSize, Allocator.Persistent);
        velocity = new NativeArray<Vector3>(initialSize, Allocator.Persistent);
        radius = new NativeArray<float>(initialSize, Allocator.Persistent);
        linearDrag = new NativeArray<float>(initialSize, Allocator.Persistent);
        mass = new NativeArray<float>(initialSize, Allocator.Persistent);
        restitution = new NativeArray<float>(initialSize, Allocator.Persistent);
        collisions = new NativeArray<Collision>(initialSize * 2, Allocator.Persistent);
        CollisionManager.collisionBufferSize = initialSize * 2;
        bTransforms = new Transform[initialSize];
        ballMaterials = new Material[initialSize];
    }

    public void Dispose()
    {
        try
        {
            isStatic.Dispose();
            position.Dispose();
            velocity.Dispose();
            radius.Dispose();
            linearDrag.Dispose();
            mass.Dispose();
            restitution.Dispose();
            collisions.Dispose();
        }
        catch (ObjectDisposedException)
        {
            Debug.Log("already disposed");
            return;
        }
    }



}

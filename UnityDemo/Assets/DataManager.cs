using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq.Expressions;
using Unity.Burst;
using Unity.Collections;
using Unity.Collections.LowLevel.Unsafe;
using Unity.Jobs;
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
    public NativeArray<int> color_id;
    public Material[] ballMaterials;
    public static readonly Color[] colors =
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
        color_id = new NativeArray<int> (initialSize, Allocator.Persistent);
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
            color_id.Dispose();
        }
        catch (ObjectDisposedException)
        {
            Debug.Log("already disposed");
            return;
        }
    }

    //[BurstCompile(CompileSynchronously = true)]
    //public struct CompleteJob : IJob
    //{
    //    public float deltaTime;
    //    public DataManager DM;
    //    public float BoundaryBoxSize;
    //    public void Execute() 
    //    {
    //        //update movement
    //        for (int i = 0; i < DM.ballCount; i++)
    //        {
    //            if (!DM.isStatic[i])
    //            {
    //                //apply drag
    //                DM.velocity[i] *= 1 - (DM.linearDrag[i] * deltaTime);
    //                //apply velocity
    //                DM.position[i] += (DM.velocity[i] * deltaTime);

    //            }
    //            //check if static element
    //            if (DM.isStatic[i])
    //                continue;
    //            //apply boundary conditions
    //            float radius = DM.radius[i];
    //            Vector3 position = DM.position[i];
    //            Vector3 velocity = DM.velocity[i];

    //            if (position.x > BoundaryBoxSize - radius)
    //            {
    //                position.x = BoundaryBoxSize - radius;
    //                velocity.x = -velocity.x;
    //            }
    //            else if (position.x < -BoundaryBoxSize + radius)
    //            {
    //                position.x = -BoundaryBoxSize + radius;
    //                velocity.x = -velocity.x;
    //            }
    //            if (position.y > BoundaryBoxSize - radius)
    //            {
    //                position.y = BoundaryBoxSize - radius;
    //                velocity.y = -velocity.y;
    //            }
    //            else if (position.y < -BoundaryBoxSize + radius)
    //            {
    //                position.y = -BoundaryBoxSize + radius;
    //                velocity.y = -velocity.y;
    //            }
    //            if (position.z > BoundaryBoxSize - radius)
    //            {
    //                position.z = BoundaryBoxSize - radius;
    //                velocity.z = -velocity.z;
    //            }
    //            else if (position.z < -BoundaryBoxSize + radius)
    //            {
    //                position.z = -BoundaryBoxSize + radius;
    //                velocity.z = -velocity.z;
    //            }
    //            DM.position[i] = position;
    //            DM.velocity[i] = velocity;

    //        }
    //    }
    //}

}

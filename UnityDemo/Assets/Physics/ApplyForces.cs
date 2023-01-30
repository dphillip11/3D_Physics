using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using Unity.Burst;
using Unity.Collections;
using Unity.Jobs;
using UnityEngine;


public static class ApplyForces
{
    
    [BurstCompile]
    public struct resolveCollisionsJob : IJobParallelFor
    {
        public NativeArray<Collision> collisions;
        public NativeArray<int> color_id;
        public NativeArray<Vector3> velocity;
        public NativeArray<float> mass;
        public NativeArray<float> restitution;

        public void Execute(int i)
        {
            if (!collisions[i].isActive)
                return;
            if (collisions[i].isResolved)
                return;
            int ID1 = collisions[i].bodyID1;
            int ID2 = collisions[i].bodyID2;
            color_id[ID1] = (color_id[ID2] + 1) % 6;
            color_id[ID2] = (color_id[ID2] + 1) % 6;
            Vector3 relativeVelocity = velocity[ID1] - velocity[ID2];
            float collisionSpeed = Vector3.Dot(relativeVelocity, collisions[i].normal);
            if (collisionSpeed > 0)
            {
                float elasticity = (restitution[ID2] + restitution[ID1]) / 2;
                Vector3 impulse = -(1 + elasticity) * collisions[i].normal * collisionSpeed / (mass[ID1] + mass[ID2]);
                velocity[ID1] += impulse * mass[ID2];
                velocity[ID2] -= impulse * mass[ID1];
            }
            var tmpCollision = collisions[i];
            tmpCollision.isResolved = true;
            collisions[i] = tmpCollision;
        }
    }
    public static DataManager arrays;
    
    public static void resolveCollisions(float deltaTime)
    {
        int collisionBufferSize = CollisionManager.collisionBufferSize;
      

        resolveCollisionsJob job = new resolveCollisionsJob
        {
            collisions = arrays.collisions,
            color_id = arrays.color_id,
            velocity = arrays.velocity,
            mass = arrays.mass,
            restitution = arrays.restitution,
        };
        

        JobHandle handle = job.Schedule(collisionBufferSize, 1);

        // Wait for the job to complete
        handle.Complete();
        for(int i = 0; i < arrays.ballCount; i++)
        {
            arrays.ballMaterials[i].color = DataManager.colors[arrays.color_id[i]];
        }
    }
}

using Unity.Burst;
using Unity.Collections;
using Unity.Jobs;
using UnityEngine;


[BurstCompile(FloatMode = FloatMode.Fast)]
public struct MoveJob : IJobParallelFor
{
    public int ballCount;
    public float deltaTime;
    public NativeArray<bool> isStatic;
    public NativeArray<Vector3> positions;
    public NativeArray<Vector3> velocities;
    public NativeArray<float> linearDrags;
    public NativeArray<float> radii;
    public float BoundaryBoxSize;

    public void Execute(int i)
    {
            if (!isStatic[i])
            {
                //apply drag
                velocities[i] *= 1 - (linearDrags[i] * deltaTime);
                //apply velocity
                positions[i] += (velocities[i] * deltaTime);

            }
            //check if static element
            if (isStatic[i])
                return;
            //apply boundary conditions
            float radius = radii[i];
            Vector3 position = positions[i];
            Vector3 velocity = velocities[i];

            if (position.x > BoundaryBoxSize - radius)
            {
                position.x = BoundaryBoxSize - radius;
                velocity.x = -velocity.x;
            }
            else if (position.x < -BoundaryBoxSize + radius)
            {
                position.x = -BoundaryBoxSize + radius;
                velocity.x = -velocity.x;
            }
            if (position.y > BoundaryBoxSize - radius)
            {
                position.y = BoundaryBoxSize - radius;
                velocity.y = -velocity.y;
            }
            else if (position.y < -BoundaryBoxSize + radius)
            {
                position.y = -BoundaryBoxSize + radius;
                velocity.y = -velocity.y;
            }
            if (position.z > BoundaryBoxSize - radius)
            {
                position.z = BoundaryBoxSize - radius;
                velocity.z = -velocity.z;
            }
            else if (position.z < -BoundaryBoxSize + radius)
            {
                position.z = -BoundaryBoxSize + radius;
                velocity.z = -velocity.z;
            }
            positions[i] = position;
            velocities[i] = velocity;

        }
    }

public static class ApplyMotion
{
    public static float BoundaryBoxSize;
    public static DataManager arrays;


    public static void Apply(float deltaTime)
    {
        var move = new MoveJob
        {
            ballCount = arrays.ballCount,
            deltaTime = deltaTime,
            isStatic = arrays.isStatic,
            radii = arrays.radius,
            positions = arrays.position,
            velocities = arrays.velocity,
            linearDrags = arrays.linearDrag,
            BoundaryBoxSize = BoundaryBoxSize,

        };
        JobHandle handle = move.Schedule(arrays.ballCount, 1);

        // Wait for the job to complete
        handle.Complete();

    }

}
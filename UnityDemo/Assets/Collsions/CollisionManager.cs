using UnityEngine;
using Unity.Jobs;
using Unity.Burst;
using Unity.Collections;
using Unity.VisualScripting;
using JetBrains.Annotations;

[BurstCompile]
struct collisionsJob : IJob
{
    public NativeArray<Collision> collisions;
    public NativeArray<float> radius;
    public NativeArray<Vector3> position;
    public int ballCount;
    public int collisionCursor;
    public int collisionBufferSize;
    public int CHECKING_METHOD;
    public void Execute()
    {
        for (int i = 0; i < ballCount; i++)
        {
            for (int j = i + 1; j < ballCount; j++)
            {

                Collision col = new Collision();
                col.isActive = true;

                float sumOfRadii = radius[i] + radius[j];
                float distance;

                if (CHECKING_METHOD == 1)
                {
                    float radiiSquared = sumOfRadii * sumOfRadii;
                    Vector3 difference = position[i] - position[j];
                    float distance_squared = difference.x * difference.x + difference.y * difference.y + difference.z * difference.z;
                    if (distance_squared > radiiSquared)
                        continue;
                    else
                        distance = Mathf.Sqrt(distance_squared);
                }
                else if (CHECKING_METHOD == 2)
                {
                    distance = Vector3.Distance(position[i], position[j]);
                    if (distance > sumOfRadii)
                        continue;
                }
                else
                {
                    Vector3 difference = position[i] - position[j];
                    float totalDifference = Mathf.Abs(difference.x) + Mathf.Abs(difference.y) + Mathf.Abs(difference.z);
                    if (totalDifference > 3 * sumOfRadii)
                    {
                        continue;
                    }
                    else
                        distance = Vector3.Magnitude(difference);
                }


                float overlap = sumOfRadii - distance;
                // log collision properties
                col.isResolved = false;
                col.normal = (position[j] - position[i]).normalized;
                col.position = position[i] + (col.normal * (radius[i] - (overlap / 2)));
                // adjust objects so they are just touching
                position[j] -= col.normal * (overlap / 2);
                position[j] += col.normal * (overlap / 2);
                col.bodyID1 = i;
                col.bodyID2 = j;

                //add to collision log
                collisions[collisionCursor] = col;

                if (collisionCursor < collisionBufferSize - 1)
                {
                    collisionCursor++;
                }
                else
                {
                    collisionCursor = 0;
                }

            }

        }
    }
}
public static class CollisionManager
{
    static public DataManager arrays;
    static private int collisionCursor = 0;
    static public int collisionBufferSize;
    static private int CHECKING_METHOD = 2;


    public static void checkCollisions()
    {
        var job = new collisionsJob

        { position = arrays.position, collisions = arrays.collisions, ballCount = arrays.ballCount, radius = arrays.radius, collisionBufferSize = collisionBufferSize, collisionCursor = collisionCursor, CHECKING_METHOD=CHECKING_METHOD
        };
        job.Run();
    }

}


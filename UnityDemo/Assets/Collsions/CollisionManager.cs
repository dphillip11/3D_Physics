using UnityEngine;
using Unity.Jobs;
using Unity.Burst;
using Unity.Collections;
using Unity.VisualScripting;


//[BurstCompile]
struct collisionsJob : IJob
{
    public void Execute()
    {
        CollisionManager.checkCollisionsJob();
    }
}
public static class CollisionManager
{

    static public Collision[] collisions;
    static private int collisionCursor = 0;
    static public int collisionBufferSize;
    static private int CHECKING_METHOD = 2;


    public static void checkCollisions()
    {
        var job = new collisionsJob();
        job.Run();
    }
    public static void checkCollisionsJob()
    {
        for (int i = 0; i < BallManager.ballCount; i++)
        {
            for (int j = i + 1; j < BallManager.ballCount; j++)
            {

                Collision col = new Collision();
                col.isActive = true;

                float sumOfRadii = BallManager.balls[i].radius + BallManager.balls[j].radius;
                float distance;

                if (CHECKING_METHOD == 1)
                {
                    float radiiSquared = sumOfRadii * sumOfRadii;
                    Vector3 difference = BallManager.balls[i].position - BallManager.balls[j].position;
                    float distance_squared = difference.x * difference.x + difference.y * difference.y + difference.z * difference.z;
                    if (distance_squared > radiiSquared)
                        continue;
                    else
                        distance = Mathf.Sqrt(distance_squared);
                }
                else if (CHECKING_METHOD == 2)
                {
                    distance = Vector3.Distance(BallManager.balls[i].position, BallManager.balls[j].position);
                    if (distance > sumOfRadii)
                        continue;
                }
                else
                {
                    Vector3 difference = BallManager.balls[i].position - BallManager.balls[j].position;
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
                col.normal = (BallManager.balls[j].position - BallManager.balls[i].position).normalized;
                col.position = BallManager.balls[i].position + (col.normal * (BallManager.balls[i].radius - (overlap / 2)));
                // adjust objects so they are just touching
                BallManager.balls[i].position -= col.normal * (overlap / 2);
                BallManager.balls[j].position += col.normal * (overlap / 2);
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


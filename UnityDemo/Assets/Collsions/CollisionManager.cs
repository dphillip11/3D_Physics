using UnityEngine;
using Unity.Jobs;
using Unity.Burst;



[BurstCompile]
struct collisionsJob: IJob
{
    public int shapesCursor;
    public void Execute()
    {
        CollisionManager.checkCollisionsJob(shapesCursor);
    }
}
public static class CollisionManager
{

    static public int collisionBufferSize;
    static public Collision[] collisions;
    static private int collisionCursor;
    public static void init()
    {
        collisions = new Collision[collisionBufferSize];
        collisionCursor = 0;
    }

    public static void checkCollisions()
    {
        var job = new collisionsJob();
        job.shapesCursor = ShapeManager.shapeCursor;
        job.Run();
    }
    public static void checkCollisionsJob(int shapeCursor)
    {
        for (int i = 0; i < shapeCursor; i++)
        {
            for (int j = i + 1; j < shapeCursor; j++)
            {
                Collision col = new Collision();
                col.isActive = true;

                //check how far apart
                float distance = Vector3.Distance(ShapeManager.shapes[i].body.centre, ShapeManager.shapes[j].body.centre);
                // check if overlapping
                float sumOfRadii = ((SphereComponent)ShapeManager.shapes[i]).radius + ((SphereComponent)ShapeManager.shapes[j]).radius;
                if (distance < sumOfRadii)
                {
                    float overlap = sumOfRadii - distance;
                    // log collision properties
                    col.isResolved = false;
                    col.normal = (ShapeManager.shapes[j].body.centre - ShapeManager.shapes[i].body.centre).normalized;
                    col.position = ShapeManager.shapes[i].body.centre + (col.normal * (((SphereComponent)ShapeManager.shapes[i]).radius - (overlap / 2)));
                    // adjust objects so they are just touching
                    ShapeManager.shapes[i].body.centre -= col.normal * (overlap / 2);
                    ShapeManager.shapes[j].body.centre += col.normal * (overlap / 2);
                    col.collider0 = ShapeManager.shapes[i].shapeIdentifier;
                    col.collider1 = ShapeManager.shapes[j].shapeIdentifier;
                
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
}


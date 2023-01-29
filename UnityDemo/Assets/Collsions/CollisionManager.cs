using UnityEngine;


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
        for (int i = 0; i < ShapeManager.shapes.Length; i ++)
        {
            for (int j = i + 1; j < ShapeManager.shapes.Length; j++)
            {
                if (ShapeManager.shapes[i] == null)
                    return;
                if (ShapeManager.shapes[j] == null) 
                    break;

                if (ShapeManager.shapes[i].getType() != "empty" && ShapeManager.shapes[j].getType() != "empty")
                {
                    CollisionManager.checkCollision(ShapeManager.shapes[i], ShapeManager.shapes[j]);
                }

            }

        }
    }

    public static void checkCollision(ShapeComponent shapeA, ShapeComponent shapeB)
    {
        Collision col = new Collision();
        if (shapeA.getType() == "sphere" && shapeB.getType() == "sphere")
        {
            //check how far apart
            float distance = Vector3.Distance(shapeA.body.centre, shapeB.body.centre);
            // check if overlapping
            float sumOfRadii = ((SphereComponent)shapeA).radius + ((SphereComponent)shapeB).radius;
            if (distance < sumOfRadii)
            {
                float overlap = sumOfRadii - distance;
                // log collision properties
                col.wasResolved = false;
                col.normal = (shapeB.body.centre - shapeA.body.centre).normalized;
                col.position = shapeA.body.centre + (col.normal * (((SphereComponent)shapeA).radius - (overlap/2)));
                // adjust objects so they are just touching
                shapeA.body.centre -= col.normal * (overlap/2);
                shapeB.body.centre += col.normal * (overlap / 2);
                col.collider0 = shapeA.body;
                col.collider1 = shapeB.body;
            }
        }
        if (!col.wasResolved)
        {
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


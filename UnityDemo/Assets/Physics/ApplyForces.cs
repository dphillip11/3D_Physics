using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class ApplyForces 
{
    public static DataManager arrays;
    public static void resolveCollisions(float deltaTime)
    {
        int collisionBufferSize = CollisionManager.collisionBufferSize;
        for (int i = 0; i < collisionBufferSize; i++)
        {
            if (!arrays.collisions[i].isActive)
                return;
            if (arrays.collisions[i].isResolved) 
                continue;
            int ID1 = arrays.collisions[i].bodyID1;
            int ID2 = arrays.collisions[i].bodyID2;
            Vector3 relativeVelocity = arrays.velocity[ID1] - arrays.velocity[ID2];
            float collisionSpeed = Vector3.Dot(relativeVelocity, arrays.collisions[i].normal);
            if (collisionSpeed > 0)
            {
                float elasticity = (arrays.restitution[ID2] + arrays.restitution[ID1]) / 2;
                Vector3 impulse = -(1 + elasticity) * arrays.collisions[i].normal * collisionSpeed / (arrays.mass[ID1] + arrays.mass[ID2]);
                arrays.velocity[ID1] += impulse * arrays.mass[ID2];
                arrays.velocity[ID2]-= impulse * arrays.mass[ID1];
            }
            var tmpCollision = arrays.collisions[i];
            tmpCollision.isResolved= true;
            arrays.collisions[i] = tmpCollision;
        }
    }
}

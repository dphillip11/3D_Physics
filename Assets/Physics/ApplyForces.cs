using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class ApplyForces 
{
    public static void resolveCollisions(float deltaTime)
    {
        foreach(Collision col in CollisionManager.collisions)
        {
            if (col == null)
                return;
            if (col.wasResolved) continue;
            Vector3 relativeVelocity = col.collider0.velocity - col.collider1.velocity;
            float collisionSpeed = Vector3.Dot(relativeVelocity, col.normal);
            if (collisionSpeed > 0)
            {
                float elasticity = (col.collider1.restitution + col.collider0.restitution) / 2;
                Vector3 impulse = -(1 + elasticity) * col.normal * collisionSpeed/(col.collider0.mass + col.collider1.mass);
                col.collider0.velocity += impulse * col.collider1.mass;
                col.collider1.velocity -= impulse * col.collider0.mass;
            }
            col.wasResolved = true;
        }
    }
}

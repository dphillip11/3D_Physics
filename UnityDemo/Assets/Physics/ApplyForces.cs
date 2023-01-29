using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class ApplyForces 
{
    public static void resolveCollisions(float deltaTime)
    {
        for (int i = 0; i < CollisionManager.collisionBufferSize; i++)
        {
            if (!CollisionManager.collisions[i].isActive)
                return;
            if (!CollisionManager.collisions[i].isResolved) 
                continue;
            Vector3 relativeVelocity = ShapeManager.shapes[CollisionManager.collisions[i].collider0].body.velocity - ShapeManager.shapes[CollisionManager.collisions[i].collider1].body.velocity;
            float collisionSpeed = Vector3.Dot(relativeVelocity, CollisionManager.collisions[i].normal);
            if (collisionSpeed > 0)
            {
                float elasticity = (ShapeManager.shapes[CollisionManager.collisions[i].collider1].body.restitution + ShapeManager.shapes[CollisionManager.collisions[i].collider0].body.restitution) / 2;
                Vector3 impulse = -(1 + elasticity) * CollisionManager.collisions[i].normal * collisionSpeed/(ShapeManager.shapes[CollisionManager.collisions[i].collider0].body.mass + ShapeManager.shapes[CollisionManager.collisions[i].collider1].body.mass);
                ShapeManager.shapes[CollisionManager.collisions[i].collider0].body.velocity += impulse * ShapeManager.shapes[CollisionManager.collisions[i].collider1].body.mass;
                ShapeManager.shapes[CollisionManager.collisions[i].collider1].body.velocity -= impulse * ShapeManager.shapes[CollisionManager.collisions[i].collider0].body.mass;
            }
            CollisionManager.collisions[i].isResolved = true;
        }
    }
}

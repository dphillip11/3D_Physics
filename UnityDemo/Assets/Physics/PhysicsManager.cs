using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class PhysicsManager
{
    public static void Apply(float deltaTime)
    {
        ApplyMotion.Apply(deltaTime);
        CollisionManager.checkCollisions();
        ApplyForces.resolveCollisions(deltaTime);
    }

 
}

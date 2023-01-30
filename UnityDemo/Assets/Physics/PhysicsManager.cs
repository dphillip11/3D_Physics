using System.Collections;
using System.Collections.Generic;
using Unity.Burst;
using Unity.Jobs;
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

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class PhysicsManager
{
    public static int poolOfBodiesSize = 100;
    public static PointMass[] bodies;
    public static int bodyCursor = 0;
    
    public static void init()
    {   
        if (bodies == null)
            bodies= new PointMass[poolOfBodiesSize];
    }

    public static void AddBody(PointMass body)
    {
        //check array is initialised
        if (bodies == null) { init(); }
        //point to null body
        while (bodies[bodyCursor] != null)
        {
            bodyCursor++;
            // if exceed pool size, extend pool
            if (bodyCursor > poolOfBodiesSize - 1)
            {
                poolOfBodiesSize *= 2;
                var tempBodies = new PointMass[poolOfBodiesSize];
                bodies.CopyTo(tempBodies, 0);
                bodies = tempBodies;
            }
        }        

        bodies[bodyCursor] = body;
    }
    public static void Apply(float deltaTime)
    {
        ApplyMotion.Apply(deltaTime);
        ApplyMotion.ApplyBoundaryConditions();
        CollisionManager.checkCollisions();
        ApplyForces.resolveCollisions(deltaTime);
    }

 
}

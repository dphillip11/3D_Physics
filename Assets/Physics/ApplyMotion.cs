using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class ApplyMotion
{
    public static float BoundaryBoxSize;
    public static void Apply(float deltaTime)
    {
        foreach (PointMass body in PhysicsManager.bodies)
        {
            //check if empty element
            if (body == null)
                return;
            if (!body.isStatic)
            {

                body.velocity += (body.acceleration * deltaTime);
                //apply drag
                body.velocity *= 1 - (body.linearDrag * deltaTime);
                body.acceleration *= 1 - (body.linearDrag * deltaTime);
                body.centre += (body.velocity * deltaTime);

            }

        }
    }

    public static void ApplyBoundaryConditions()
    {
        foreach (PointMass body in PhysicsManager.bodies)
        {
            //check if empty element
            if (body == null)
                return;
            if (!body.isStatic)
            {
                float radius = ((SphereComponent)body.shape).radius;
                if (body.centre.x > BoundaryBoxSize - radius)
                {
                    body.centre.x = BoundaryBoxSize - radius;
                    body.velocity.x = -body.velocity.x;
                }
                if (body.centre.x < -BoundaryBoxSize + radius)
                {
                    body.centre.x = -BoundaryBoxSize + radius;
                    body.velocity.x = -body.velocity.x;
                }
                if (body.centre.y > BoundaryBoxSize - radius)
                {
                    body.centre.y = BoundaryBoxSize - radius;
                    body.velocity.y = -body.velocity.y;
                }
                if (body.centre.y < -BoundaryBoxSize + radius)
                {
                    body.centre.y = -BoundaryBoxSize + radius;
                    body.velocity.y = -body.velocity.y;
                }
                if (body.centre.z > BoundaryBoxSize - radius)
                {
                    body.centre.z = BoundaryBoxSize - radius;
                    body.velocity.z = -body.velocity.z;
                }
                if (body.centre.z < -BoundaryBoxSize + radius)
                {
                    body.centre.z = -BoundaryBoxSize + radius;
                    body.velocity.z = -body.velocity.z;
                }

            }

        }
    }
}

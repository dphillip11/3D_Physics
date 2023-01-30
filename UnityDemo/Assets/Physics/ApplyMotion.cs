using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class ApplyMotion
{
    public static float BoundaryBoxSize;
    public static DataManager arrays;

    public static void Apply(float deltaTime)
    {
        for (int i = 0; i < arrays.ballCount; i++)
        {
            //check if empty element
            if (arrays.mass[i] == 0)
                return;
            if (!arrays.isStatic[i])
            {
                //apply drag
                arrays.velocity[i] *= 1 - (arrays.linearDrag[i] * deltaTime);
                //apply velocity
                arrays.position[i] += (arrays.velocity[i] * deltaTime);

            }

        }
    }
    public static void ApplyBoundaryConditions()
    {
        for (int i = 0; i < arrays.ballCount; i++)
        {
            //check if empty element
            if (arrays.mass[i] == 0)
                return;
            if (!arrays.isStatic[i])
            {
                float radius = arrays.radius[i];
                Vector3 position = arrays.position[i];
                Vector3 velocity = arrays.velocity[i];

                if (position.x > BoundaryBoxSize - radius)
                {
                    position.x = BoundaryBoxSize - radius;
                    velocity.x = -velocity.x;
                }
                else if (position.x < -BoundaryBoxSize + radius)
                {
                    position.x = -BoundaryBoxSize + radius;
                    velocity.x = -velocity.x;
                }
                if (position.y > BoundaryBoxSize - radius)
                {
                    position.y = BoundaryBoxSize - radius;
                    velocity.y = -velocity.y;
                }
                else if (position.y < -BoundaryBoxSize + radius)
                {
                    position.y = -BoundaryBoxSize + radius;
                    velocity.y = -velocity.y;
                }
                if (position.z > BoundaryBoxSize - radius)
                {
                    position.z = BoundaryBoxSize - radius;
                    velocity.z = -velocity.z;
                }
                else if (position.z < -BoundaryBoxSize + radius)
                {
                    position.z = -BoundaryBoxSize + radius;
                    velocity.z = -velocity.z;
                }
                arrays.position[i] = position;
                arrays.velocity[i] = velocity;

            }

        }
    }
}
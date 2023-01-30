using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class ApplyMotion
{
    public static float BoundaryBoxSize;
    public static void Apply(float deltaTime)
    {
        for (int i = 0; i < BallManager.ballCount; i++)
        {
            //check if empty element
            if (BallManager.balls[i].mass == 0)
                return;
            if (!BallManager.balls[i].isStatic)
            {
                //apply drag
                BallManager.balls[i].velocity *= 1 - (BallManager.balls[i].linearDrag * deltaTime);
                BallManager.balls[i].position += (BallManager.balls[i].velocity * deltaTime);

            }

        }
    }

    public static void ApplyBoundaryConditions()
    {
        for (int i = 0; i < BallManager.ballCount; i++)
        {
            //check if empty element
            if (BallManager.balls[i].mass == 0)
                return;
            if (!BallManager.balls[i].isStatic)
            {
                float radius = BallManager.balls[i].radius;
                if (BallManager.balls[i].position.x > BoundaryBoxSize - radius)
                {
                    BallManager.balls[i].position.x = BoundaryBoxSize - radius;
                    BallManager.balls[i].velocity.x = -BallManager.balls[i].velocity.x;
                }
                if (BallManager.balls[i].position.x < -BoundaryBoxSize + radius)
                {
                    BallManager.balls[i].position.x = -BoundaryBoxSize + radius;
                    BallManager.balls[i].velocity.x = -BallManager.balls[i].velocity.x;
                }
                if (BallManager.balls[i].position.y > BoundaryBoxSize - radius)
                {
                    BallManager.balls[i].position.y = BoundaryBoxSize - radius;
                    BallManager.balls[i].velocity.y = -BallManager.balls[i].velocity.y;
                }
                if (BallManager.balls[i].position.y < -BoundaryBoxSize + radius)
                {
                    BallManager.balls[i].position.y = -BoundaryBoxSize + radius;
                    BallManager.balls[i].velocity.y = -BallManager.balls[i].velocity.y;
                }
                if (BallManager.balls[i].position.z > BoundaryBoxSize - radius)
                {
                    BallManager.balls[i].position.z = BoundaryBoxSize - radius;
                    BallManager.balls[i].velocity.z = -BallManager.balls[i].velocity.z;
                }
                if (BallManager.balls[i].position.z < -BoundaryBoxSize + radius)
                {
                    BallManager.balls[i].position.z = -BoundaryBoxSize + radius;
                    BallManager.balls[i].velocity.z = -BallManager.balls[i].velocity.z;
                }

            }

        }
    }
}

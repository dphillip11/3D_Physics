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
            if (CollisionManager.collisions[i].isResolved) 
                continue;
            int ID1 = CollisionManager.collisions[i].bodyID1;
            int ID2 = CollisionManager.collisions[i].bodyID2;
            Vector3 relativeVelocity = BallManager.balls[ID1].velocity - BallManager.balls[ID2].velocity;
            float collisionSpeed = Vector3.Dot(relativeVelocity, CollisionManager.collisions[i].normal);
            if (collisionSpeed > 0)
            {
                float elasticity = (BallManager.balls[ID2].restitution + BallManager.balls[ID1].restitution) / 2;
                Vector3 impulse = -(1 + elasticity) * CollisionManager.collisions[i].normal * collisionSpeed/(BallManager.balls[ID1].mass + BallManager.balls[ID2].mass);
                BallManager.balls[ID1].velocity += impulse * BallManager.balls[ID2].mass;
                BallManager.balls[ID2].velocity -= impulse * BallManager.balls[ID1].mass;
            }
            CollisionManager.collisions[i].isResolved = true;
        }
    }
}

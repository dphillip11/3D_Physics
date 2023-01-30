using Unity.Collections;
using UnityEngine;

public static class BallManager
{
    public static int ballCount = 0;
    public static int arraySize;
    public static Transform[] ballTransforms;
    public static BallComponent[] balls;


    public static void increaseBallCount()
    {
        ballCount++;
        if (ballCount > arraySize - 1)
        {
            arraySize *= 2;
            var tempBalls = new BallComponent[arraySize];
            balls.CopyTo(tempBalls,0);
            balls = tempBalls;
            var tempBallTransforms = new Transform[arraySize];
            ballTransforms.CopyTo(tempBallTransforms, 0);
            ballTransforms = tempBallTransforms;
        }
    }
}

using System.Collections;
using System.Collections.Generic;
using TMPro;
using Unity.Collections;
using UnityEngine;

public class BallSpawner : MonoBehaviour
{
 
    public GameObject ballPrefab;
    public int initialArraySize = 500;
    public TextMeshProUGUI ballCount;


    public BallComponent getNewBallComponent()
    {
        BallComponent newBall = new BallComponent();
        newBall.velocity = Random.Range(-30,30) * Vector3.one;
        newBall.isStatic = false;
        newBall.linearDrag = 0;
        newBall.mass = 1;
        newBall.restitution = 1;
        return newBall;
    }

    void Start()
    {
        BallManager.arraySize= initialArraySize;
        BallManager.ballTransforms = new Transform[initialArraySize];
        BallManager.balls = new BallComponent[initialArraySize];
        CollisionManager.collisions = new Collision[(initialArraySize * 2)];
        CollisionManager.collisionBufferSize = initialArraySize * 2;
    }



    public void CreateBall()
    {
        var size = Random.Range(1, 10);
        var spawnPos = new Vector3(randomPos(), randomPos(), randomPos());
        //create game object
        var newSphere = GameObject.Instantiate(ballPrefab, spawnPos, Quaternion.identity);
        newSphere.transform.localScale = size * Vector3.one;
        newSphere.GetComponent<SpeedColor>().ID = BallManager.ballCount;
        BallManager.ballTransforms[BallManager.ballCount] = newSphere.transform;
        //create component
        BallComponent newBall = getNewBallComponent();
        newBall.radius = size/2;
        newBall.position = spawnPos;
        newBall.ID = BallManager.ballCount;
        BallManager.balls[BallManager.ballCount] = newBall;
        BallManager.increaseBallCount();
        ballCount.text = "Balls: " + BallManager.ballCount;
    }

    public void CreateBalls(int n)
    {
        for (int i = 0; i < n; i++)
        {
            CreateBall();
        }
    }

    public float randomPos()
    {
        return Random.Range(-ApplyMotion.BoundaryBoxSize, ApplyMotion.BoundaryBoxSize);
    }
}



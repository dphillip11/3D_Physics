using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    public float initialBoundarySize;
    public int poolSize;
    public float minBallSize;
    public float maxBallSize;
    public float maxBallSpeed;
    DataManager arrays;
    BallSpawner ballSpawner;
    public GameObject ballPrefab;
    public TextMeshProUGUI ballCount;
    private bool inPlay = true;
    // Start is called before the first frame update
    void Start()
    {
        //create data structures
        arrays= new DataManager();
        arrays.initialSize = arrays.currentCapacity = poolSize;
        arrays.Init();
        //create ball spawner
        ballSpawner= new BallSpawner();
        ballSpawner.arrays = arrays;
        ballSpawner.ballPrefab = ballPrefab;
        ballSpawner.ballCount= ballCount;
        //create references to data manager
        ApplyMotion.arrays = arrays;
        ApplyForces.arrays = arrays;
        CollisionManager.arrays = arrays;

        //set up boundary box
        ApplyMotion.BoundaryBoxSize = initialBoundarySize * 5;
        GameObject.Find("BoundingBox").transform.localScale = Vector3.one * initialBoundarySize;
    }  

    // Update is called once per frame
    void Update()
    {
        if (inPlay)
        {
            if (Input.GetKeyUp(KeyCode.Escape))
            {
                inPlay= false;
                arrays.Dispose();
                Application.Quit();
                return;
            }
            PhysicsManager.Apply(Time.deltaTime);
            UpdateTransforms();
        }
        BallSpawner.minBallSize = minBallSize;
        BallSpawner.maxBallSize = maxBallSize;
        BallSpawner.maxBallSpeed= maxBallSpeed;

    }

    void UpdateTransforms()
    {
        for ( int i = 0; i < arrays.ballCount; i++ )
        {
            arrays.bTransforms[i].position = arrays.position[i];
        }
        
    }

    public void spawnBalls(int n)
    {
        ballSpawner.CreateBalls(n);
    }

    public void spawnOpposingBalls()
    {
        ballSpawner.CreateOpposingBalls();
    }

    private void OnApplicationQuit()
    {
        arrays.Dispose();
    }
}

using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    public float boundarySize;
    // Start is called before the first frame update
    void Start()
    {
        ApplyMotion.BoundaryBoxSize = boundarySize * 5;
        GameObject.Find("BoundingBox").transform.localScale = Vector3.one * boundarySize;
    }  

    // Update is called once per frame
    void Update()
    {
        PhysicsManager.Apply(Time.deltaTime);
        UpdateTransforms();

    }

    void UpdateTransforms()
    {
        for ( int i = 0; i < BallManager.ballCount; i++ )
        {
            BallManager.ballTransforms[i].position = BallManager.balls[i].position;
        }
    }
}

using System.Collections;
using System.Collections.Generic;
using TMPro;
using Unity.Collections;
using UnityEngine;
using UnityEngine.UIElements;

public class BallSpawner
{
    public DataManager arrays;
    public GameObject ballPrefab;
    public TextMeshProUGUI ballCount;
    public void initialiseBallComponents(int index)
    {
        arrays.isStatic[index] = false;
        arrays.position[index] = randomPos();
        arrays.velocity[index] = randomPos().normalized * Random.Range(20,100);
        arrays.radius[index] = 0.5f;
        arrays.linearDrag[index] = 0.05f;
        arrays.mass[index] = 1;
        arrays.restitution[index] = 0.95f;
    }

    public void CreateBall()
    {
        int index = arrays.ballCount;
        if (index > arrays.currentCapacity - 1)
        {
            Debug.Log("allocated memory filled");
            return;
        }
        initialiseBallComponents(index);
        var radius = Random.Range(1, 20);
        arrays.radius[index] = radius;
        arrays.mass[index] = radius * 4;
        var spawnPos = arrays.position[index];
        //create game object
        var newSphere = GameObject.Instantiate(ballPrefab, spawnPos, Quaternion.identity);
        newSphere.transform.localScale = radius * 2 * Vector3.one;
        arrays.ballMaterials[arrays.ballCount] = newSphere.GetComponent<Renderer>().material;
        arrays.bTransforms[index] = newSphere.transform;
        arrays.ballCount++;
        ballCount.text = "Balls: " + arrays.ballCount;
    }

    public void CreateBalls(int n)
    {
        for (int i = 0; i < n; i++)
        {
            CreateBall();
        }
    }

    public Vector3 randomPos()
    {
        return new Vector3(Random.Range(-ApplyMotion.BoundaryBoxSize, ApplyMotion.BoundaryBoxSize), Random.Range(-ApplyMotion.BoundaryBoxSize, ApplyMotion.BoundaryBoxSize), Random.Range(-ApplyMotion.BoundaryBoxSize, ApplyMotion.BoundaryBoxSize));
    }
}



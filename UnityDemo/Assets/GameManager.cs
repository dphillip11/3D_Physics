using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    public float gameTime = 0;
    public GameObject spherePrefab;
    
    // Start is called before the first frame update
    void Start()
    {
        PhysicsManager.poolOfBodiesSize = 100;
        PhysicsManager.init();
        ShapeManager.shapePoolSize = 100;
        ShapeManager.init();
        CollisionManager.collisionBufferSize = ShapeManager.shapePoolSize * 2;
        CollisionManager.init();
        ApplyMotion.BoundaryBoxSize = 40;
    }

    public float randomPos()
    {
        return Random.Range(-ApplyMotion.BoundaryBoxSize, ApplyMotion.BoundaryBoxSize);
    }

    public void CreateShape(string type)
    {
        if (type == "sphere")
        {
            var size = Random.Range(1, 10);
            var spawnPos = new Vector3(randomPos(), randomPos(), randomPos());
            var newSphere = GameObject.Instantiate(spherePrefab, spawnPos, Quaternion.identity);
            newSphere.GetComponent<PointMass>().mass = size;
            newSphere.GetComponent<SphereComponent>().radius = size / 2;
            newSphere.transform.localScale = Vector3.one * size/2;
        }
    }

    public void CreateShapes(int n)
    {
        for (int i = 0; i < n; i++)
        {
            CreateShape("sphere");
        }
    }

    // Update is called once per frame
    void Update()
    {
        gameTime+= Time.deltaTime;
        PhysicsManager.Apply(Time.deltaTime);
        ShapeManager.Render(Time.deltaTime);
    }
}

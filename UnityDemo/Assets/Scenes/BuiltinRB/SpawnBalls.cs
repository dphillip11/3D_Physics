using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class SpawnBalls : MonoBehaviour
{
    public GameObject BallPrefab;
    public int ballCount;
    public TextMeshProUGUI text;
    public float boundarySize;
    public float minSize;
    public float maxSize;
    // Start is called before the first frame update
    void Start()
    {
        ballCount = 0; 
    }

    public void spawnBalls(int n) 
    { 
        for (int i =0; i < n; i++)
        {
            var spawnPos = new Vector3 (Random.Range(-boundarySize, boundarySize), Random.Range(-boundarySize, boundarySize), Random.Range(-boundarySize, boundarySize));
            var ball = Instantiate(BallPrefab);
            ball.transform.position = spawnPos;
            ball.transform.localScale = Vector3.one * Random.Range(minSize,maxSize);
            ball.GetComponent<Rigidbody>().velocity = new Vector3(Random.Range(-100, 100), Random.Range(-100, 100), Random.Range(-100, 100));
            ballCount++;
            text.text = "Balls: " + ballCount;
        }
    }

}

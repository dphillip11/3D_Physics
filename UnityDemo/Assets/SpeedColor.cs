using UnityEngine;

public class SpeedColor : MonoBehaviour
{
    public float minSpeed = 0f;
    public float maxSpeed = 10f;
    public Color minColor = Color.blue;
    public Color maxColor = Color.red;
    public int ID;

 

    void Update()
    {
        float speed = BallManager.balls[ID].velocity.magnitude;
        float t = Mathf.InverseLerp(minSpeed, maxSpeed, speed);
        GetComponent<Renderer>().material.color = Color.Lerp(minColor, maxColor, t);
    }
}

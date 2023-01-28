using UnityEngine;

public class SpeedColor : MonoBehaviour
{
    public float minSpeed = 0f;
    public float maxSpeed = 10f;
    public Color minColor = Color.blue;
    public Color maxColor = Color.red;

    private PointMass body;

    void Start()
    {
        body = GetComponent<PointMass>();
    }

    void Update()
    {
        float speed = body.velocity.magnitude;
        float t = Mathf.InverseLerp(minSpeed, maxSpeed, speed);
        GetComponent<Renderer>().material.color = Color.Lerp(minColor, maxColor, t);
    }
}

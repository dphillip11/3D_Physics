using UnityEngine;

public class FPSCounter : MonoBehaviour
{
    private float deltaTime;
    private int fps;
    private GUIStyle style;
    private float updateInterval = 0.5f;
    private float accumulator = 0;
    private int frames = 0;

    private void Start()
    {
        style = new GUIStyle();
        style.fontSize = 40;
        style.normal.textColor = Color.white;
    }

    private void Update()
    {
        accumulator += Time.unscaledDeltaTime;
        frames++;

        if (accumulator > updateInterval)
        {
            fps = (int)(frames / accumulator);
            frames = 0;
            accumulator = 0;
        }
    }

    private void OnGUI()
    {
        int w = Screen.width, h = Screen.height;

        Rect rect = new Rect(0, 0, w, h * 5 / 100);
        style.alignment = TextAnchor.UpperLeft;
        GUI.Label(rect, "FPS: " + fps.ToString("F2"), style);
    }
}

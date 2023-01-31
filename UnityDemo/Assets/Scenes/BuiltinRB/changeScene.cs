
using UnityEngine;
using UnityEngine.SceneManagement;

public class changeScene : MonoBehaviour
{
   

    public void ChangeScene()
    {
        try
        {
            ApplyForces.arrays.Dispose();
        } 
        catch { }
        int scene = SceneManager.GetActiveScene().buildIndex;
        int nextScene = scene == 0 ? 1 : 0;
        SceneManager.LoadScene(nextScene);
    }



}

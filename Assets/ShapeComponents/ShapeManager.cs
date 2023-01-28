using System.Collections;
using System.Collections.Generic;
using System.Data;
using UnityEditor;
using UnityEngine;

public static class ShapeManager
{
    public static int shapePoolSize = 100;
    private static int shapeCursor = 0;
    public static ShapeComponent[] shapes;
    
    public static void init()
    {
        if (shapes == null)
        {
            shapes = new ShapeComponent[shapePoolSize];
        }
    }


    public static void AddShape(ShapeComponent shape)
    {
        //check array is initialised
        if (shapes == null) { init(); }
        // point to null shape
        while (shapes[shapeCursor] != null)
        {
            shapeCursor++;
            // if exceed pool size
            if (shapeCursor > shapePoolSize - 1)
            {
                shapePoolSize *= 2;
                var tempShapes = new ShapeComponent[shapePoolSize];
                shapes.CopyTo(tempShapes, 0);
                shapes = tempShapes;
            }
        }     
        
        shapes[shapeCursor] = shape;
    }

    public static void Render(float deltaTime)
    {
        foreach (var shape in shapes)
        {
            try
            {
                shape.transform.position = shape.body.centre;
            }
            catch 
            {
                return;
            }
           
        }
    }

}

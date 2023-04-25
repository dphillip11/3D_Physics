# 3D Physics and rendering

This repository contains a number of learning experiments related to 3D rendering and physics. The "OpenGLExperiments" repository contains what is essentially summed up in the demo programs. I have implemented a ball physics simulation utilising multithreading and spatial partitioning, an .obj viewer using Phong lighting and a ray traced Newton's cradle predominantly in GLSL. Some features that are not demonstrated in the demo programs inlcude geometry shaders for subdividing spheres and calculating normals for triangles as well as an attempt at hierarchical transform components.

### Click the image to view the demo programs in action:

[![Watch the video](https://img.youtube.com/vi/h-1O1ScTmVw/maxresdefault.jpg)](https://youtu.be/h-1O1ScTmVw)

### This video shows a stable framerate achieved using an octree:

[![Watch the video](https://img.youtube.com/vi/LdWEugD0k1E/maxresdefault.jpg)](https://youtu.be/LdWEugD0k1E)


The Unity Demo folder has an implementation of a ball physics simulation that uses the burst compiler and IJobParallelFor components serving as a benchmark for collision detection performance. I have structured the data to conform to the ECS architecture such that similar data is neatly grouped in contiguous arrays maximizing cache hits. It performs well in editor but WebGL doesn't seem to permit the burst capability for this demo. The performance already is to a large extent limited by the rendering thread which takes a little bit longer than running the scripts in the in-editor profiler. I am mostly concerned about the collision performance here as I will be performing the same job in C++ so I won't be attempting any rendering optimisations.

### Click the image to run the demo program:

[![Title](https://play-static.unity.com/20230129/p/images/8c512348-7207-48b3-bdef-6d2952ecf81a_Screenshot_20230129_185738.png)](https://play.unity.com/webgl/fa00616c-37ec-4343-af24-c34660c46cc8)




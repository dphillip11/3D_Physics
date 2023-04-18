# 3D Physics and rendering

This repository contains a number of learning experiments related to 3D rendering and physics. The "practice project" repository contains what is essentially summed up in the demo programs. I have implemented a ball physics simulation utilising concurrency and a bucket allocator, an .obj viewer using Phong lighting and a ray tracing demo predominantly in GLSL.

### Click the image to view the demo programs in action:

[![Watch the video](https://img.youtube.com/vi/h-1O1ScTmVw/maxresdefault.jpg)](https://youtu.be/h-1O1ScTmVw)

The Unity Demo folder has an implementation of a ball physics simulation that uses the burst compiler and IJobParallelFor components serving as a benchmark for collision detection performance. It is getting close to the speed of the built in rigid bodies and colliders. Better management of jobs, possibly smaller jobs with very simple instructions and equally sized input and output may work. The performance already is limited by the rendering thread which takes a little bit longer than running the scripts in the in-editor profiler. 




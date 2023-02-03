# 3DRendering

I have a plan to firstly make a simple 3D physics simulation, spheres and planes initially, using C++ and render it using modern OpenGL. I think I will try to create a 3D pong style game where the bat moves along 2 axes but I'm not sure how playable it will be, maybe a trail effect/ conveniently placed light sources will help. I will then get to work on cubes and add some angular momentum at which point I guess multithreading is going to be more important. I'm going to try to form an ECS architecture to deal with the collisions, physics and rendering in a performant and easily threaded way.

The Unity Demo folder has an implementation of a ball physics simulation that uses the burst compiler and IJobParallelFor components. It is getting close to the speed of the built in rigid bodies and colliders. Better management of jobs, possibly smaller jobs with very simple instructions and equally sized input and output may work. The performance already is limited by the rendering thread which takes a little bit longer than running the scripts in the in-editor profiler.

What could go wrong?

[![primitives](https://drive.google.com/uc?id=1fqzTVI4VXuE5oN_h8q2zPGesyKbIMQzb)](https://drive.google.com/uc?id=1fqzTVI4VXuE5oN_h8q2zPGesyKbIMQzb)


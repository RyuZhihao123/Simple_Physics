# Real-time_Physics_RyuZhihao123

This system is devised for simulating the `collision detection` in `C++` with OpenGL and Qt platform. 

We knew that, the most complicated collision approaches provided by existing engines, are often not exactly the `real` collision!!!! For example, in Unity platform, the mesh Colliders have to be marked as **Convex** for colliding with other Mesh Colliders. Generally, it's enough for most game functions.

However, for some specific conditions that require to process **free-form, manifold objects**, we have to devise and adopt a more plausible method. No doubt such kind of methods must be time-cosuming. Here, we provide a way much simple implementation for detecting the collision among the free-form meshs (we take the efficiency into account as much as posible).

### Not yet finished!!!!

1. add textures and other rendering techniques (current code is just a rough version.).
2. bugs (sometimes the ball might fly out of the container. check the `intersectTriangle`. Perhaps because the mesh I use is two-sided.)
3. this version can `only` process TRIANGLE meshes! If necessray, we could further make it support other kinds of meshes.
4. add gravity, resistance and energy loss.

<div align=center><img width="600" src="https://github.com/RyuZhihao123/Simple_Physics/blob/master/img1.png"/></div>







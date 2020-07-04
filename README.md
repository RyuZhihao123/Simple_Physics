# Simple_Physics

This system is devised for simulating the `collision detection`. 

We knew that, the most complicated collision approaches provided by existing engines, are often not exactly the `real` collision!!!! In Unity platform, the mesh Colliders have to be marked as **Convex** for colliding with other Mesh Colliders. Generally, it's enough for most game functions.

However, for some specific conditions that require to process **free-form, manifold objects**, we have to devise and adopt a more plausible method. No doubt such kind of methods must be time-cosuming. Here, we provide a way much simple inplementation for detecting the collision among the free-form meshs (we take the efficiency into account as much as posible).

### Not yet finished!!!!

1. add textures.
2. bug (sometimes the ball might fly out of the container. check the `intersectTriangle`)
3. current code can `only` process TRIANGLE meshes! If necessray, we can make it support other kinds of meshes.
4. add gravity, resistance and energy loss.

<div align=center><img width="600" src="https://github.com/RyuZhihao123/Simple_Physics/blob/master/img1.png"/></div>







# Simple_Physics

This system is devised for simulating the `collision detection`. 

We knew that, the most complicated collision approaches provided by existing engines, are often not exactly the `real` collision!!!! In Unity platform, the mesh Colliders have to be marked as **Convex** for colliding with other Mesh Colliders. It's enough for most game functions.

However, for some specific conditions that require to process **free-form, manifold objects**, we have to devise and adopt a more plausible method. No doubt such kind of methods must be time-cosuming. Here, we provide a way much simple inplementation for detect the collision among the free-form meshs (we take the efficiency into account as much as posible).




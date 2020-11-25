# PortalProject

Names: Andrew Hack, Ian Meadows
Project: Portal

How to run:

make
./final


How to move:
Use w, a, s, and d to move around.
Use the arrow keys to look around.

----------------------------------------------
CODE CREDIT:
Stencil buffer: started with code from learnopengl, but the code is so different at this point that it’s not the same at all really.
Borrowed the Vertex function from ex8 in order to create sphere-like objects.

Camera movement code uses information from learnopengl.com.

Multiple lighting: Vertex and fragment shader code is taken from: https://www.geeks3d.com/20091013/shader-library-phong-shader-with-multiple-lights-glsl/
Has since been changed to work with shadows, but shadows are still a work in progress.

Shadow code is taken from example 36. This does not work yet though.

Any other code reuse is referenced in the code

-----------------------------------------------
THINGS TO PAY ATTENTION TO:

PORTALS
- get close, far away, try different angles
- They are NOT hard-coded to work at the specific positions, and can be rotated and put anywhere in the room, although only rotations on the y-axis work properly. (I need to figure out quaternions to make other rotations work right)
- The portals are ‘seamless’, meaning that it functions kind of like a window looking out the other portal. The view updates with your perspective, creating an illusion that makes it seem like it’s just a hole to another room we built to mirror the first, even though there is only one room in our scene.
- The portals DO NOT function with a framebuffer, they instead use a stencil buffer. First, the scene is drawn to screen, keeping track of where the portals are in the stencil buffer, with a different value for each portal. The scene is then redrawn from a new perspective, but only the parts of the screen indicated as a portal by the stencil buffer are redrawn. This happens recursively for a set number of times, allowing the portal to ‘see itself’. (if you don’t get it, I’m sorry. It’s really hard to explain without pictures.)
- The colored outline on the portal is done through a shader , this outline will become a solid oval when the portal has maxed out its recursive rendering.

LIGHTING
- There are 3 lights in the scene. 2 of them are static and one is moving. The moving one is a default white light. One of the static lights is a specular blue light. The other static light is a red specular light. The lighting is applied to the scene through 2 shaders: The SceneShader.frag and the SceneShader.vert.

SCENE(a minor detail, but still cool)
- The scene is generated from a file. The file our program looks for is SceneInfo.txt. You can add pre created objects with position, rotation, and scale. You can also add walls and floors. With these you can add a texture to these as well as give them a position, rotation, and scale.

-------------------------------------------
Things we plan to add:
- Shadows: shadows are currently being worked on, but they are not showing up for some reason.
- Shadows with multiple lights
- Better scene creation. The ability to add lights to the scene and position the camera through the text file.
- An actual scene with more fine-tuned details (texture variety, rubble, vines)
- A way to see the portals in action in different locations
- Anti-aliasing(Stretch goal)

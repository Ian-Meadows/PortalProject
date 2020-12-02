Names: Andrew Hack, Ian Meadows
Project: Portal

How to run:

make
./final

CONTROLS:
Use w, a, s, and d to move around.
Use the arrow keys to look around.
Numbers 1-5 swap portal positions and teleport you to a new location to look at them

1: Portals across from each other, can see loop through 5 iterations of portal
2: right angle, shows portals can simply be rotated around the y-axis and still work
3: different heights and non 90 degree turns work as well
4: shows how the portal views can not necessarily be rendered from the same angle when seeing themselves, each recursive portal has to re-align its view
5: I thought it looked nice

----------------------------------------------
CODE CREDIT:
Stencil buffer: started with code from learnopengl, but the code is so different at this point that it’s not the same at all really.
Borrowed the Vertex function from ex8 in order to create sphere-like objects.

Camera movement code uses information from learnopengl.com.

Multiple lighting: Vertex and fragment shader code is taken from: https://www.geeks3d.com/20091013/shader-library-phong-shader-with-multiple-lights-glsl/

Normal mapping: fragment shader code and knowledge taken from:
http://ogldev.atspace.co.uk/www/tutorial26/tutorial26.html, https://learnopengl.com/Advanced-Lighting/Normal-Mapping, and https://stackoverflow.com/questions/5255806/how-to-calculate-tangent-and-binormal

Any other code reuse is referenced in the code

-----------------------------------------------
TEXTURE CREADIT:
All textures and normal maps were taken from Portal and Portal 2


-----------------------------------------------
THINGS TO PAY ATTENTION TO:

PORTALS
- get close, far away, try different angles
- PRESS NUM 1-5 FOR DIFFERENT PORTAL POSITIONS IN THE ROOM
- You can see yourself, you are a floating head of Steve from Minecraft
- They are NOT hard-coded to work at the specific positions, and can be rotated and put anywhere in the room, although only rotations on the y-axis work properly. (I need to figure out quaternions to make other rotations work right)
- The portals are ‘seamless’, meaning that it functions kind of like a window looking out the other portal. The view updates with your perspective, creating an illusion that makes it seem like it’s just a hole to another room we built to mirror the first, even though there is only one room in our scene.
- The portals DO NOT function with a framebuffer, they instead use a stencil buffer. First, the scene is drawn to screen, keeping track of where the portals are in the stencil buffer, with a different value for each portal. The scene is then redrawn from a new perspective, but only the parts of the screen indicated as a portal by the stencil buffer are redrawn. This happens recursively for a set number of times, allowing the portal to ‘see itself’. (if you don’t get it, I’m sorry. It’s really hard to explain without pictures.)
- The colored outline on the portal is done through a shader , this outline will become a solid oval when the portal has maxed out its recursive rendering.

LIGHTING
- There are 3 lights in the scene. 2 of them are static and one is moving. The moving one is a default white light. One of the static lights is a specular blue light. The other static light is a red specular light. The lighting is applied to the scene through 2 shaders: The SceneShader.frag and the SceneShader.vert.

NORMAL MAPPING
- The floor and ceiling show this off really well. There is now a secondary texture that can be loaded for walls and floors through the scene loader. This texture is a normal map. The fragment shader will use this normal map to calculate the normals for each fragment being rendered. This adds a really nice 3D effect to the flat walls and floors. In order to do this I needed to use the library glm to help out with matrix manipulations. 

SCENE(a minor detail, but still cool)
- The scene is generated from a file. The file our program looks for is SceneInfo.txt. You can add pre created objects with position, rotation, and scale. You can also add walls and floors. With these you can add a texture to these as well as give them a position, rotation, and scale.

-------------------------------------------



WHO DID WHAT:
Quick Note: we did not realize that our local git was not set up to show who was committing for a while at the start. During this time, work on portals was Andrew and work on Shaders was Ian.
Andrew Hack:
- Portals
- Construction of the ‘props’ (dropper, camera, cube)
- Construction of the scene (except the lights)
- Pulling textures and normal maps from the games(Portal and Portal 2) and applying them to objects

Ian Meadows:
- Lighting
- Multiple Lights
- Normal Mapping
- Ability to edit the scene from a file so we could refresh scene without re-making and restarting

Note: I tried to create shadows. The issue I ran into was first the code from example 36 was for directional shadows. The problem with this was that I was using point lights. I found a tutorial on learnopengl.com that explained how to make point shadows. This involved using a cube map and a framebuffer. The issue I ran into was that I was using an older version of OpenGL than every example I looked at. These examples wanted me to use a Geometry shader and do a call on the framebuffer that is not supported with the version of OpenGL that I was using. I spent a very long time on this trying to bypass the need to use a Geometry shader and avoid using the unsupported call to the frame buffer, but sadly I was unable to.


/*
//  Per Pixel Lighting shader with texture

varying vec3 View;

varying vec3 Normal;

#define MAX_LIGHTS 8
#define NUM_LIGHTS 3
varying vec3 Light;

void main()
{
   //  Vertex location in modelview coordinates
   vec4 P = gl_ModelViewMatrix * gl_Vertex;
   //  Light position
   Light  = gl_LightSource[0].position.xyz - P.xyz;
   //  Normal
   Normal = gl_NormalMatrix * gl_Normal;
   //  Eye position
   View  = -P.xyz;
   //  Texture
   gl_TexCoord[0] = gl_MultiTexCoord0;
   //  Set vertex position
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
*/


// taking: https://www.geeks3d.com/20091013/shader-library-phong-shader-with-multiple-lights-glsl/
/*
varying vec3 normal, eyeVec;
varying vec4 Ambient;
#define MAX_LIGHTS 8
#define NUM_LIGHTS 1
varying vec3 lightDir[MAX_LIGHTS];
void main()
{	
  gl_Position = ftransform();
  Ambient = gl_FrontMaterial.emission + gl_FrontLightProduct[0].ambient + gl_LightModel.ambient*gl_FrontMaterial.ambient;
  gl_TexCoord[0] = gl_MultiTexCoord0;		
  normal = gl_NormalMatrix * gl_Normal;
  vec4 vVertex = gl_ModelViewMatrix * gl_Vertex;
  eyeVec = -vVertex.xyz;
  int i;


  vec4 X = gl_ModelViewMatrix*gl_Vertex;
  gl_TexCoord[1].s = dot(gl_EyePlaneS[1],X);
  gl_TexCoord[1].t = dot(gl_EyePlaneT[1],X);
  gl_TexCoord[1].p = dot(gl_EyePlaneR[1],X);
  gl_TexCoord[1].q = dot(gl_EyePlaneQ[1],X);
  gl_TexCoord[1] /= gl_TexCoord[1].q;


  for (i=0; i<NUM_LIGHTS; ++i)
    lightDir[i] = vec3(gl_LightSource[i].position.xyz - vVertex.xyz);
}
*/



//  Shadow Vertex shader

varying vec3 View;
varying vec3 Light;
varying vec3 Normal;
varying vec4 Ambient;

void main()
{
   //
   //  Lighting values needed by fragment shader
   //
   //  Vertex location in modelview coordinates
   vec3 P = vec3(gl_ModelViewMatrix * gl_Vertex);
   //  Light position
   Light  = vec3(gl_LightSource[0].position) - P;
   //  Normal
   Normal = gl_NormalMatrix * gl_Normal;
   //  Eye position
   View  = -P;
   //  Ambient color
   Ambient = gl_FrontMaterial.emission + gl_FrontLightProduct[0].ambient + gl_LightModel.ambient*gl_FrontMaterial.ambient;

   //  Texture coordinate for fragment shader
   gl_TexCoord[0] = gl_MultiTexCoord0;
   //  Generate eye position coordinates
   vec4 X = gl_ModelViewMatrix*gl_Vertex;
   gl_TexCoord[1].s = dot(gl_EyePlaneS[1],X);
   gl_TexCoord[1].t = dot(gl_EyePlaneT[1],X);
   gl_TexCoord[1].p = dot(gl_EyePlaneR[1],X);
   gl_TexCoord[1].q = dot(gl_EyePlaneQ[1],X);
   gl_TexCoord[1] /= gl_TexCoord[1].q;

   //  Set vertex position
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
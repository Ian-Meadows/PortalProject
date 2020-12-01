#version 130


// taking: https://www.geeks3d.com/20091013/shader-library-phong-shader-with-multiple-lights-glsl/

varying vec3 normal, eyeVec;
varying vec4 Ambient;
#define MAX_LIGHTS 8
#define NUM_LIGHTS 1
varying vec3 lightDir[MAX_LIGHTS];

varying vec3 fragPos;

uniform mat4 model;
out mat4 inModal;





void main()
{	
  gl_Position = ftransform();
  Ambient = gl_FrontMaterial.emission + gl_FrontLightProduct[0].ambient + gl_LightModel.ambient*gl_FrontMaterial.ambient;
  gl_TexCoord[0] = gl_MultiTexCoord0;		
  normal = gl_NormalMatrix * gl_Normal;
  vec4 vVertex = gl_ModelViewMatrix * gl_Vertex;
  eyeVec = -vVertex.xyz;


   for(int i=0; i<NUM_LIGHTS; ++i){
      lightDir[i] = vec3(gl_LightSource[i].position.xyz - vVertex.xyz);
   }
      
   //probably wrong
   fragPos = (model * gl_Vertex).xyz;
   inModal = model;
}
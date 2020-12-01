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



/*
//  Shadow Vertex shader

varying vec3 View;
varying vec3 Light;
varying vec3 Normal;
varying vec4 Ambient;

out mat3 TBN;



mat3 CalcTBN(vec3 fragPos){
    // compute derivations of the world position
    vec3 p_dx = dFdx(fragPos);
    vec3 p_dy = dFdy(fragPos);
    // compute derivations of the texture coordinate
    vec2 tc_dx = dFdx(gl_TexCoord[0].st);
    vec2 tc_dy = dFdy(gl_TexCoord[0].st);
    // compute initial tangent and bi-tangent
    vec3 t = normalize( tc_dy.y * p_dx - tc_dx.y * p_dy );
    vec3 b = normalize( tc_dy.x * p_dx - tc_dx.x * p_dy ); // sign inversion
    // get new tangent from a given mesh normal
    vec3 n = normalize(Normal);
    vec3 x = cross(n, t);
    t = cross(x, n);
    t = normalize(t);
    // get updated bi-tangent
    x = cross(b, n);
    b = cross(n, x);
    b = normalize(b);
    mat3 tbn = mat3(t, b, n);
    return tbn;
}



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
   

   //  Set vertex position
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;


   


   //probably wrong
   //fragPos = gl_Position;


   TBN = CalcTBN(gl_Position);
}
*/
#version 130

// taken from: https://www.geeks3d.com/20091013/shader-library-phong-shader-with-multiple-lights-glsl/

varying vec3 normal, eyeVec;
varying vec4 Ambient;
#define MAX_LIGHTS 8
#define NUM_LIGHTS 1
varying vec3 lightDir[MAX_LIGHTS];
uniform sampler2D tex;
uniform sampler2D normalMap;

uniform bool hasNormalMap;

varying vec3 fragPos;
uniform vec3 viewPos;
in mat4 inModal;

// normal map info taken from http://ogldev.atspace.co.uk/www/tutorial26/tutorial26.html, https://learnopengl.com/Advanced-Lighting/Normal-Mapping, and https://stackoverflow.com/questions/5255806/how-to-calculate-tangent-and-binormal



vec4 GetTangent(){
    vec3 p_dx = dFdx(fragPos);
    vec3 p_dy = dFdy(fragPos);
    // compute derivations of the texture coordinate
    vec2 tc_dx = dFdx(gl_TexCoord[0].st);
    vec2 tc_dy = dFdy(gl_TexCoord[0].st);
    // compute initial tangent and bi-tangent
    vec3 t = normalize( tc_dy.y * p_dx - tc_dx.y * p_dy );
    // get new tangent from a given mesh normal
    vec3 n = normalize(normal);
    vec3 x = cross(n, t);
    t = cross(x, n);
    t = normalize(t);
    return vec4(t, 1.0);
}

vec3 CalcBumpedNormal()
{
    vec3 Normal = normalize(normal);
    vec3 Tangent = normalize(inModal * GetTangent()).xyz;
    Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
    vec3 Bitangent = cross(Tangent, Normal);
    vec3 BumpMapNormal = texture(normalMap, gl_TexCoord[0].st).xyz;
    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
    vec3 NewNormal;
    mat3 TBN = mat3(Tangent, Bitangent, Normal);
    NewNormal = TBN * BumpMapNormal;
    NewNormal = normalize(NewNormal);
    return NewNormal;
}


vec4 PhoneLighting()
{
  vec4 final_color = Ambient;
  vec3 N;
  if(hasNormalMap){
    N = CalcBumpedNormal();
  }
  else{
    N = normalize(normal);
  }
  //vec3 N = normalize(normal);
  //vec3 N = texture(normalMap, gl_TexCoord[0].st).rgb;
  for(int i=0; i<NUM_LIGHTS; ++i)
  {  

    vec3 L = normalize(lightDir[i]);
    float lambertTerm = dot(N,L);
    if (lambertTerm > 0.0)
    {
      //final_color += gl_LightSource[i].diffuse * gl_FrontMaterial.diffuse * lambertTerm;	
      final_color += gl_FrontLightProduct[0].diffuse * lambertTerm;

      //specular
      vec3 E = normalize(eyeVec);
      vec3 R = reflect(-L, N);
      float specular = pow(max(dot(R, E), 0.0), gl_FrontMaterial.shininess);
      //final_color += gl_LightSource[i].specular * gl_FrontMaterial.specular * specular;	
      final_color += gl_FrontLightProduct[0].specular * specular;	
    }
  }
  return final_color;
}



void main (void)
{
    gl_FragColor = PhoneLighting() * texture2D(tex,gl_TexCoord[0].st);
  
}

/*
//  Shadow Fragment shader

varying vec3 View;
varying vec3 Light;
varying vec3 Normal;
varying vec4 Ambient;
uniform sampler2D tex;
uniform sampler2D normalMap;

uniform bool hasNormalMap;

in mat3 TBN;




vec4 phong()
{
   //  Emission and ambient color
   vec4 color = Ambient;

   //  N is the object normal
  vec3 N = normalize(Normal);
  //  L is the light vector
  vec3 L = normalize(Light);

  //  Diffuse light is cosine of light and normal vectors
  float Id = dot(L,N);
  if (Id>0.0)
  {
      //  Add diffuse
      color += Id*gl_FrontLightProduct[0].diffuse;
      //  R is the reflected light vector R = 2(L.N)N - L
      vec3 R = reflect(-L,N);
      //  V is the view vector (eye vector)
      vec3 V = normalize(View);
      //  Specular is cosine of reflected and view vectors
      float Is = dot(R,V);
      if (Is>0.0) color += pow(Is,gl_FrontMaterial.shininess)*gl_FrontLightProduct[0].specular;
  }
   
   //  Return result
   return color;
}

void main()
{
   //  Compute pixel lighting modulated by texture
   if(hasNormalMap){
      gl_FragColor = phong() * texture2D(normalMap, gl_TexCoord[0].st);
   }
   else{
      gl_FragColor = phong() * texture2D(tex,gl_TexCoord[0].st);
   }
   
}
*/

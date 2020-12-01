#version 130



varying vec3 normal, eyeVec;
varying vec4 Ambient;
#define MAX_LIGHTS 8
#define NUM_LIGHTS 4
varying vec3 lightDir[MAX_LIGHTS];
uniform sampler2D tex;
uniform sampler2D normalMap;

uniform bool hasNormalMap;

varying vec3 fragPos;
uniform vec3 viewPos;
in mat4 inModal;

// normal map information taken from http://ogldev.atspace.co.uk/www/tutorial26/tutorial26.html, https://learnopengl.com/Advanced-Lighting/Normal-Mapping, and https://stackoverflow.com/questions/5255806/how-to-calculate-tangent-and-binormal
// Multiple lights information taken from: https://www.geeks3d.com/20091013/shader-library-phong-shader-with-multiple-lights-glsl/


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

  for(int i=0; i<NUM_LIGHTS; ++i)
  {  

    vec3 L = normalize(lightDir[i]);
    float lambertTerm = dot(N,L);
    if (lambertTerm > 0.0)
    {	
      final_color += gl_FrontLightProduct[i].diffuse * lambertTerm;

      //specular
      vec3 E = normalize(eyeVec);
      vec3 R = reflect(-L, N);
      float specular = pow(max(dot(R, E), 0.0), gl_FrontMaterial.shininess);

      final_color += gl_FrontLightProduct[i].specular * specular;	
    }
  }
  return final_color;
}



void main (void)
{
    gl_FragColor = PhoneLighting() * texture2D(tex,gl_TexCoord[0].st);
  
}

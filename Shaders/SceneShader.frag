/*

//  Per Pixel Lighting shader with texture

varying vec3 View;

varying vec3 Normal;
uniform sampler2D tex;

#define MAX_LIGHTS 8
#define NUM_LIGHTS 3
varying vec3 Light;

void main()
{



   //  N is the object normal
   vec3 N = normalize(Normal);
   //  L is the light vector
   vec3 L = normalize(Light);
   //  R is the reflected light vector R = 2(L.N)N - L
   vec3 R = reflect(-L,N);
   //  V is the view vector (eye vector)
   vec3 V = normalize(View);

   //  Diffuse light is cosine of light and normal vectors
   float Id = max(dot(L,N) , 0.0);
   //  Specular is cosine of reflected and view vectors
   float Is = (Id>0.0) ? pow(max(dot(V,R),0.0) , gl_FrontMaterial.shininess) : 0.0;

   
   

   //  Sum color types
   vec4 color = gl_FrontMaterial.emission

  + gl_FrontLightProduct[0].ambient + 0.3
  + Id*gl_FrontLightProduct[0].diffuse

  + Is*gl_FrontLightProduct[0].specular;

   //  Apply texture
   gl_FragColor = color * texture2D(tex,gl_TexCoord[0].xy);


}
*/

// taken from: https://www.geeks3d.com/20091013/shader-library-phong-shader-with-multiple-lights-glsl/

varying vec3 normal, eyeVec;
varying vec4 Ambient;
#define MAX_LIGHTS 8
#define NUM_LIGHTS 1
varying vec3 lightDir[MAX_LIGHTS];
uniform sampler2D tex;
uniform sampler2DShadow depth;

void main (void)
{
  vec4 final_color = Ambient;
  if(shadow2DProj(depth,gl_TexCoord[1]).a==1.0){
    // final_color= gl_FrontLightModelProduct.sceneColor;
    vec3 N = normalize(normal);
    int i;
    for (i=0; i<NUM_LIGHTS; ++i)
    {  
      vec3 L = normalize(lightDir[i]);
      float lambertTerm = dot(N,L);
      if (lambertTerm > 0.0)
      {
        //final_color += gl_LightSource[i].diffuse * gl_FrontMaterial.diffuse * lambertTerm;	
        final_color += gl_FrontLightProduct[0].diffuse * lambertTerm;
        vec3 E = normalize(eyeVec);
        vec3 R = reflect(-L, N);
        float specular = pow(max(dot(R, E), 0.0), gl_FrontMaterial.shininess);
        //final_color += gl_LightSource[i].specular * gl_FrontMaterial.specular * specular;	
        final_color += gl_FrontLightProduct[0].specular * specular;	
      }
    }
    gl_FragColor = final_color * texture2D(tex,gl_TexCoord[0].xy);		
  }
  
  gl_FragColor = final_color * texture2D(tex,gl_TexCoord[0].xy);
}

//  portal shader with texture (no lighting and portal effect)

varying vec3 View;
varying vec3 Light;
varying vec3 Normal;
uniform sampler2D tex;
uniform float sizeX;
uniform float sizeY;
uniform float offset;

//the 0 or 1(orange or blue)
uniform int portalNumber;


float OvalTest(float h, float k, float b, float a, float x, float y){
   return (pow(x - h, 2.0) / pow(a, 2.0)) + (pow(y - k, 2.0) / pow(b, 2.0));
}


//check if less then 1
int InCircle(vec2 pos)
{
   //center x
   float h = 0.5;
   //center y
   float k = 0.5;

   float b = (sizeY - offset)/2.0;
   float a = (sizeX - offset)/2.0;

   //(x-h)^2/a^2 + (y-k)^2/b^2
   //float result = (pow(pos.x - h, 2.0) / pow(a, 2.0)) + (pow(pos.y - k, 2.0) / pow(b, 2.0));
   
   if(OvalTest(h, k, b, a, pos.x, pos.y) <= 1.0){
      return 0;
   }
   else{
      b = sizeY/2.0;
      a = sizeX/2.0;
      if(OvalTest(h, k, b, a, pos.x, pos.y) <= 1.0){
         return 1;
      }
      else{
         return 2;
      }
   }
}

void main()
{
   //  N is the object normal
   vec3 N = normalize(Normal);
   //  V is the view vector (eye vector)
   vec3 V = normalize(View);


   int value = InCircle(gl_TexCoord[0].xy);
   if(value == 0){
      //  Apply texture
      gl_FragColor = texture2D(tex,gl_TexCoord[0].xy);
   }
   else if(value == 1){//apply outline
      if(portalNumber == 0){
         gl_FragColor = vec4(1, 0.6, 0, 1);
      }
      else{
         gl_FragColor = vec4(0.3, 0.3, 1, 1);
      }
   }
   else{ //outside ring
      gl_FragColor = vec4(0, 0, 0, 0);
   }

   
   
}
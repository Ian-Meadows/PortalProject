//  portal shader with texture (no lighting and portal effect)

varying vec3 View;
varying vec3 Light;
varying vec3 Normal;
uniform sampler2D tex;

void main()
{
   //  N is the object normal
   vec3 N = normalize(Normal);
   //  V is the view vector (eye vector)
   vec3 V = normalize(View);
   //  Apply texture
   gl_FragColor = texture2D(tex,gl_TexCoord[0].xy);
}
//  Set the fragment color
#version 120

varying vec4 vPos;
varying vec3 vLight;
varying vec3 vView;
varying vec3 vNormal;

void main()
{
   vec3 N = normalize(vNormal);
   //  L is the light vector
   vec3 L = normalize(vLight);
   //  R is the reflected light vector R = 2(L.N)N - L
   vec3 R = reflect(-L,N);
   //  V is the view vector (eye vector)
   vec3 V = normalize(vView);

   float Id = max(dot(L,N) , 0.0);

   float Is = (Id>0.0) ? pow(max(dot(R,V),0.0) , gl_FrontMaterial.shininess) : 0.0;


   // gl_FragColor = vec4(vPos.y/5); 
   // Black and white 
   gl_FragColor = vec4((normalize(vNormal)), 1.0);
}

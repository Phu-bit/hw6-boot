//  Set the fragment color
#version 120

varying vec4 vPos;
varying vec3 vLightDir;
varying vec3 vView;
varying vec3 vNormal;
varying vec3 vModelPos;


void main()
{
   vec4 startingColor = vPos;

   vec4 ambientColor = gl_LightSource[0].ambient;
   //  N is the normal vector
   vec3 N = normalize(vNormal);
   //  L is the light vector
   vec3 L = normalize(vLightDir);
   //  R is the reflected light vector R = 2(L.N)N - L
   vec3 R = reflect(-L,N);
   //  V is the view vector (eye vector)
   vec3 V = normalize(vView);

   float Id = max(dot(L,N) , 0.0);

   float Is = (Id>0.0) ? pow(max(dot(R,V),0.0) , gl_FrontMaterial.shininess) : 0.0;

   vec3 dx = dFdx(vModelPos);
   vec3 dy = dFdy(vModelPos);
   vec3 modelNormal = normalize(cross(dy, dx));

   float NdotL = max(0.0, -dot(modelNormal, L));

   // gl_FragColor = vec4(vPos.y/5); 

   // Black and white with lighting
   gl_FragColor = startingColor * vec4(min(ambientColor + NdotL, vec4(1.0)).rgb, 1.0);


}

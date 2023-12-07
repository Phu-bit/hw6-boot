//  Set the fragment color
#version 120

uniform float uHeight;

varying vec4 vPos;
varying vec3 vLightDir;
varying vec3 vModelPos;
varying vec3 vView;


vec4 colorDarkBlue = vec4(0.0, 0.259, 0.569, 1.0);
vec4 colorLightBlue = vec4(0.204, 0.553, 0.98, 1.0);
vec4 colorSand = vec4(1, 0.875, 0.533, 1.0);
vec4 colorGreen1 = vec4(0.024, 0.58, 0, 1.0);
vec4 colorGreen2 = vec4(0.122, 0.431, 0.0, 1.0);
vec4 colorBrown = vec4(0.6, 0.4, 0.2, 1.0);
vec4 colorWhite = vec4(1.0, 1.0, 1.0, 1.0);


void main()
{
   vec4 startingColor = vPos;

   float normalizedHeight = vPos.y / uHeight;

      // Determine color based on height
   // Define colors for different heights

   // Blend the colors based on height
   vec4 terrainColor = colorDarkBlue;
   terrainColor = mix(terrainColor, colorLightBlue, smoothstep(0.0, 0.05, normalizedHeight));
   terrainColor = mix(terrainColor, colorSand, smoothstep(0.05, 0.1, normalizedHeight));
   terrainColor = mix(terrainColor, colorGreen1, smoothstep(0.1, 0.2, normalizedHeight));
   terrainColor = mix(terrainColor, colorGreen2, smoothstep(0.2, 0.5, normalizedHeight));
   terrainColor = mix(terrainColor, colorBrown, smoothstep(0.5, 0.6, normalizedHeight));
   terrainColor = mix(terrainColor, colorWhite, smoothstep(0.6, 0.7, normalizedHeight));
   // terrainColor * vPos ;

   //  Ambient color
   vec4 ambientColor = gl_LightSource[0].ambient;
   //  L is the light vector
   vec3 L = normalize(vLightDir);
   //  V is the view vector
   vec3 V = normalize(vView);
   
   // calculating the slope of the terrain by taking the partial derivatives of the model position 
   vec3 dx = dFdx(vModelPos);
   vec3 dy = dFdy(vModelPos);
   // find the normal of the terrain by crossing the two vectors
   vec3 modelNormal = normalize(cross(dy, dx));

   float NdotL = max(0.0, -dot(modelNormal, L));

   // gl_FragColor = vec4(vPos.y/5); 
   vec4 finalLight = terrainColor * vec4(min(ambientColor + NdotL, vec4(1.0)).rgb, 1.0);
   // Black and white with lighting
   gl_FragColor = finalLight;


}

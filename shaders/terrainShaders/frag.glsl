//  Set the fragment color
#version 120

varying vec4 vPos;
varing vec3 vNormal;

void main()
{
    
   // gl_FragColor = vec4(vPos.y/5);
   // Black and white 
   gl_FragColor = vec4(vPos.y, vPos.y, vPos.y, 1.0);
}

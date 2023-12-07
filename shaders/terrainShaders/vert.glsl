// Identity vertex shader
#version 120

uniform float uTime;
uniform float uScale;
uniform float uPersistence;
uniform float uLacunarity;
uniform float uExponentiation;
uniform float uHeight;
uniform int uOctaves;
uniform vec3 uResolution;
uniform vec2 uOffset; 

uniform int uTileSize;

varying vec4 vPos;
varying vec3 vLightDir;
varying vec3 vModelPos;
varying vec3 vView;


float perlinColor;

//All Noise functions from https://gist.github.com/patriciogonzalezvivo/670c22f3966e662d2f83

// Function to interpolate between values with a smooth curve
float fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

// Simplex 2D noise
vec3 permute(vec3 x) { return mod(((x*34.0)+1.0)*x, 289.0); }

float snoise(vec2 v){
  const vec4 C = vec4(0.211324865405187, 0.366025403784439,
           -0.577350269189626, 0.024390243902439);
  vec2 i  = floor(v + dot(v, C.yy) );
  vec2 x0 = v -   i + dot(i, C.xx);
  vec2 i1;
  i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
  vec4 x12 = x0.xyxy + C.xxzz;
  x12.xy -= i1;
  i = mod(i, 289.0);
  vec3 p = permute( permute( i.y + vec3(0.0, i1.y, 1.0 ))
  + i.x + vec3(0.0, i1.x, 1.0 ));
  vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x12.xy,x12.xy),
    dot(x12.zw,x12.zw)), 0.0);
  m = m*m ;
  m = m*m ;
  vec3 x = 2.0 * fract(p * C.www) - 1.0;
  vec3 h = abs(x) - 0.5;
  vec3 ox = floor(x + 0.5);
  vec3 a0 = x - ox;
  m *= 1.79284291400159 - 0.85373472095314 * ( a0*a0 + h*h );
  vec3 g;
  g.x  = a0.x  * x0.x  + h.x  * x0.y;
  g.yz = a0.yz * x12.xz + h.yz * x12.yw;
  return 130.0 * dot(m, g);
}

float ComputeFBM(vec2 v) {
    float xs = v.x / uScale;
    float ys = v.y / uScale;
    float G = pow(2.0, -uPersistence);
    float amplitude = 1.0;
    float frequency = 1.0;
    float normalization = 0.0;
    float total = 0.0;

    for (int o = 0; o < uOctaves; ++o) {
        float noiseValue = snoise(vec2(xs * frequency, ys * frequency)) * 0.5 + 0.5;
        total += noiseValue * amplitude;
        normalization += amplitude;
        amplitude *= G;
        frequency *= uLacunarity;
    }

    total /= normalization;
    return pow(total, uExponentiation) * uHeight;
}

void main() {

  // get position
  vec4 position = gl_Vertex;

  position.xz += uOffset; // Apply the offset

  // Get the position of the vertex in world coordinates
  vec4 P = gl_ModelViewMatrix * position;

  // Get the light vector
  vec4 L = gl_LightSource[0].position ;

  // Calculating the perlin noise
  float randomOffset = ComputeFBM(position.xz);

  // Adding the perlin noise to the y coordinate
  position.y += randomOffset;

  // Calculate the light direction
  vLightDir  = L.xyz - P.xyz;
  
  // Transform position
  gl_Position = gl_ModelViewProjectionMatrix * position;

  // vPos = position;
  vPos = vec4(randomOffset);
  
  // Use color unchanged
  gl_FrontColor = gl_Color;

  // Pass the model position to the fragment shader
  vModelPos = P.xyz;

  // Pass the view vector to the fragment shader
  vView = normalize(-P.xyz);

}

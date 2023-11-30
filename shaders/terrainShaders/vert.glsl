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

uniform int uTileSize;

varying vec4 vPos;
varying vec3 vLightDir;
varying vec3 vView;
varying vec3 vNormal;
varying vec3 vModelPos;

float perlinColor;

//All Noise functions from https://gist.github.com/patriciogonzalezvivo/670c22f3966e662d2f83

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}


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

  vec4 position = gl_Vertex;
  vec4 P = gl_ModelViewMatrix * gl_Vertex;
  vec4 L = gl_LightSource[0].position ;

  float randomOffset = ComputeFBM(position.xz);
  position.y += randomOffset;

  // Calculate the gradient
  float dx = 0.001; // A small offset for sampling
  float dy = 0.001;
  float heightRight = ComputeFBM(position.xz + vec2(dx, 0.0));
  float heightUp = ComputeFBM(position.xz + vec2(0.0, dy));
  vec3 gradient = vec3(heightRight - randomOffset, heightUp - randomOffset, dx * dy) * 1.0;
  
  // Calculate the normal
  vec3 up = vec3(0.0, 1.0, 0.0);

  vec3 normal = normalize(cross(up, gradient));

  vLightDir  = L.xyz - P.xyz;
  
  // Transform position
  gl_Position = gl_ModelViewProjectionMatrix * position;

  // Pass the normal to the fragment shader if needed
  vNormal = normal; // Make sure you declare vNormal as a varying
  
  // vPos = position;
  vPos = vec4(randomOffset);
  // Use color unchanged
  gl_FrontColor = gl_Color;

  vView  = -P.xyz;
  vModelPos = P.xyz;

}

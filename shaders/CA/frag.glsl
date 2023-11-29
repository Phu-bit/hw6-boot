// Fragment shader
#version 120
uniform sampler2D uStateTexture;
uniform float uTime;
uniform vec2 uResolution;

void main() {
    vec2 texCoord = gl_FragCoord.xy / uResolution;

    // Read the current state of this cell and its neighbors
    float currentState = texture2D(uStateTexture, gl_TexCoord[0]).r;
    // ... read neighboring cells ...

    // Apply the rules of the automata to determine the next state
    float nextState = ...; // Compute the next state

    // Output the new state
    gl_FragColor = vec4(nextState, 0.0, 0.0, 1.0);
}

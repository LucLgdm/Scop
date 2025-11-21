#version 330 core

in vec3 vPos;

uniform int uColorMode;   // 0,1,2…
uniform int uUseTexture;  // ignore pour l’instant
out vec4 FragColor;

void main() {
    if (uColorMode == 0) {
        FragColor = vec4(0.6, 0.6, 0.6, 1.0);
    }
    else if (uColorMode == 1) {
        FragColor = vec4(abs(vPos), 1.0);  // debug normals approximées
    }
    else {
        FragColor = vec4((vPos.xy + 1.0) * 0.5, 0.0, 1.0); // debug UV-like
    }
}

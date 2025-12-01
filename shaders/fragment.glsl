#version 330 core

in vec3 vPos;

uniform int uColorMode;   // 0,1,2…
uniform int uUseTexture;  // ignore pour l’instant
out vec4 FragColor;

void main() {
	FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}

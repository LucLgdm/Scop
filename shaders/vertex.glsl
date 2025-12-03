#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTex;
layout(location = 3) in vec3 aColor;
layout(location = 4) in float aHasTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;
out vec3 Color;
flat out float HasTex;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTex;
	Color = aColor;
	HasTex = aHasTex;
}

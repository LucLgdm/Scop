#version 330 core

in vec2 TexCoord;
in vec3 Color;
flat in float HasTex;

uniform sampler2D uTexture;

out vec4 FragColor;

void main()
{
	if (HasTex > 0.5)
		FragColor = texture(uTexture, TexCoord);
	else
		FragColor = vec4(Color, 1.0);
}

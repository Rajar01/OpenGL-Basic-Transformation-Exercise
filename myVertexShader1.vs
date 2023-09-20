#version 400 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextureCoordinate;

out vec4 ourColor;
out vec2 ourTextureCoordinate;

uniform mat4 ourTransform;

void main()
{
	gl_Position = ourTransform * vec4(aPos, 1.0f);
	ourColor = vec4(aColor, 1.0f);
	ourTextureCoordinate = aTextureCoordinate;
}
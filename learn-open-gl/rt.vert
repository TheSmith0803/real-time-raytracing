#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 a_uv;

out vec2 uv;
out float ar;

uniform float u_aspect_ratio;

void main() {
	uv = a_uv;
	ar = u_aspect_ratio;
	gl_Position = vec4(aPos, 1.0);
}
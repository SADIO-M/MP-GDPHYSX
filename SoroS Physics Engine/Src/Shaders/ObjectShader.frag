#version 330 core

uniform vec3 color;

in vec3 fragPos;
in vec3 normCoord;
in vec2 texCoord;

out vec4 FragColor;

void main(){
	FragColor = vec4(color.x, color.y, color.z, 1.0f);
}
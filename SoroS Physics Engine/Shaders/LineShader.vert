#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 camera_view;

void main(){
	gl_Position = projection * camera_view * vec4(aPos, 1.0);
}

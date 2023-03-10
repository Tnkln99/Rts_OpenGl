#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;


void main() {
    gl_Position = projection * view * transform * vec4(aPos,1);
}
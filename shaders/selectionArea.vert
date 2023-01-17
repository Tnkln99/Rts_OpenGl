#version 450 core

in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;


void main() {
    gl_Position = projection * view * transform * vec4(aPos,1);
}
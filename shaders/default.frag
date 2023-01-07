#version 450 core

uniform vec4 soldier_color;
out vec4 color;

void main() {
    color = soldier_color;
}
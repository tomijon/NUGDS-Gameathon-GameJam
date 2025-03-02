#version 460 core

uniform float width;
uniform float height;

uniform vec2 cameraPos;

in vec2 pos;
in vec2 texCoord;

out Vertex {
    vec2 texCoord;
} OUT;

void main() {
    // vec2 relPos = pos - cameraPos;
    // vec2 screenSpace = relPos / vec2(width, height);

    OUT.texCoord = texCoord;
    gl_Position = vec4(pos, 0, 0);
}
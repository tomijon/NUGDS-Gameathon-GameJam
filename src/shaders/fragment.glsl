#version 460 core

uniform sampler2D drawTex;


in Vertex {
    vec2 texCoord;
} IN;

out vec4 fragColor;

void main() {
    fragColor = texture(drawTex, IN.texCoord);
}
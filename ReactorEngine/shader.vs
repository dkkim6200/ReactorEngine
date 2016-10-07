#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;

uniform mat4 projectionMat;
uniform mat4 translationMat;
uniform mat4 rotationMat;
uniform mat4 scaleMat;

out vec2 uv;

void main() {
    gl_Position = projectionMat * translationMat * rotationMat * scaleMat * vec4(position, 1.0);
    uv = textureCoord;
}

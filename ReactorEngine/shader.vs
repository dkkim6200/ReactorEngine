#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;

uniform mat4 transformationMat;

out vec2 uv;

void main() {
    gl_Position = transformationMat * vec4(position, 1.0);
    uv = textureCoord;
}

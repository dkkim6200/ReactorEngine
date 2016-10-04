#version 330

layout (location = 0) in vec3 position;

uniform mat4 translationMat;
uniform mat4 rotationMat;
uniform mat4 scaleMat;

out vec4 color;

void main() {
    gl_Position = translationMat * rotationMat * scaleMat * vec4(position, 1.0);
    color = vec4(clamp(position, 0.0, 1.0), 1.0);
}

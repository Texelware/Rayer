#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 textCords;

//Output variables
out vec3 Normal;
out mat4 ViewMatrix;


//Uniforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    
    ViewMatrix = view;
  

    // Transform vertex normal to world space
    Normal = mat3(transpose(inverse(model))) * vertexNormal;

    // Calculate final position
    gl_Position = projection * view * model * vec4(vertexPosition , 1.0);
}

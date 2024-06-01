#version 450 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 textCords;


uniform int u_EID;
flat out int _id; 

//Output variables
out vec3 Normal;
out mat4 ViewMatrix;
out vec2 textureCordinates;
out vec3 fragPosWorldSpace;

//Uniforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;



void main() {
    

    //Calculating world position for each fragment
    vec4 worldPosition = model * vec4(vertexPosition, 1.0);
    fragPosWorldSpace = worldPosition.xyz;

    ViewMatrix = view;
    textureCordinates = textCords;
    
    // Transform vertex normal to world space
    Normal = mat3(transpose(inverse(model))) * vertexNormal;

    // Calculate final position
    gl_Position = projection * view * model * vec4(vertexPosition , 1.0);

 


    _id = u_EID;
   
}

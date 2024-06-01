#version 450 core
layout (location = 0) in vec3 aPos;

out vec3 texCoords;

uniform mat4 s_projection;
uniform mat4 s_view;

void main()
{
    vec4 pos = s_projection * s_view * vec4(aPos, 1.0f);
    // Having z equal w will always result in a depth of 1.0f
    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
    // We want to flip the z axis due to the different coordinate systems (left hand vs right hand)
    texCoords = vec3(aPos.x, aPos.y, aPos.z);
}    
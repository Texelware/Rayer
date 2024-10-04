#version 450 core


in vec3 Normal;
in vec3 LightDir;
in flat int _id;


layout(location = 0) out vec4 FragColor;
layout(location = 1 )out int id;

uniform vec3 modelColor;

void main() {
    // Set material properties
    vec3 objectColor = modelColor; // Color depends on object selection 

    // Calculate diffuse reflection (Lambertian reflectance)
    float diffuseFactor = max(dot(Normal, LightDir), 0.0);

    // Ambient color
    vec3 ambient = vec3(5.f); // Example ambient color

    // Calculate final color (ambient + diffuse)
    vec3 diffuse = diffuseFactor * objectColor;
    //vec3 result = (ambient + diffuse) * Intensity;
    vec3 result = (ambient + diffuse) * 1.0f;

    // Output final color
    FragColor = vec4(objectColor, 1.0);

    id = int(_id);
}

#version 450 core


in vec3 Normal;
in vec3 LightDir;
in float Intensity;
in flat int _id;


layout(location = 0) out vec4 FragColor;
layout(location = 1 )out int id;

void main() {
    // Set material properties
    vec3 objectColor = vec3(1.0); // White object color

    // Calculate diffuse reflection (Lambertian reflectance)
    float diffuseFactor = max(dot(Normal, LightDir), 0.0);

    // Ambient color
    vec3 ambient = vec3(5.f); // Example ambient color

    // Calculate final color (ambient + diffuse)
    vec3 diffuse = diffuseFactor * objectColor;
    vec3 result = (ambient + diffuse) * Intensity;

    // Output final color
    FragColor = vec4(result, 1.0);

    id = int(_id);
}

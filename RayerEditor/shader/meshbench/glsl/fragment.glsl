#version 330 core

in vec3 Normal;
in mat4 ViewMatrix;

out vec4 FragColor;

//Model color uniform
uniform vec3 modelColor;

void main() {
    // Ambient color
    vec3 ambientColor = vec3(1);

    vec3 normal = normalize(Normal.xyz);

    // Light Color
    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    // Light Position (transformed to view space)
    vec3 lightPos = vec3(0.0, 100.0, 0.0);  // Example light position in world space
    vec3 lightPosViewSpace = (ViewMatrix * vec4(lightPos, 1.0)).xyz;  // Transform light position to view space

    // Direction from light to fragment (needed for diffuse lighting)
    vec3 lightDir = normalize(lightPosViewSpace);

    // Calculating diffuse
    float diffuseStrength = max(0.0, dot(lightDir, normal));
    vec3 diffuse = diffuseStrength * lightColor;

    // Combine ambient and diffuse lighting
    vec3 lighting = (ambientColor * 0.8) + (diffuse * 1);

    // Final color
    vec3 color = modelColor * lighting;

    // Output final color
    FragColor = vec4(color, 1.0);

    
    
}

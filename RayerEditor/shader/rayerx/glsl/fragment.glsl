#version 330 core

in vec3 Normal;
in mat4 ViewMatrix;

out vec4 FragColor;


void main() {
    // Ambient color
    vec3 ambientColor = vec3(1);

    vec3 normal = normalize(Normal.xyz);

    // Light Color
    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    // Light Position (transformed to view space)
    vec3 lightPos = vec3(0.0, 0.0, 20.0);  // Example light position in world space
    vec3 lightPosViewSpace = (ViewMatrix * vec4(lightPos, 1.0)).xyz;  // Transform light position to view space

    // Direction from light to fragment (needed for diffuse lighting)
    vec3 lightDir = normalize(lightPosViewSpace);

    // Calculating diffuse
    float diffuseStrength = max(0.0, dot(lightDir, normal));
    vec3 diffuse = diffuseStrength * lightColor;

    // Combine ambient and diffuse lighting
    vec3 lighting = (ambientColor * 0.8) + (diffuse * 1);

    // Calculate specular
    vec3 viewDir = normalize(-vec3(ViewMatrix[3]));  // View direction is the opposite of the camera position in view space
    vec3 reflectDir = normalize(reflect(-lightDir, normal));    // Reflect light direction around the normal
    float specularStrength = max(0.0, dot(reflectDir, viewDir));  // Calculate the angle between the reflect direction and the view direction
    specularStrength = pow(specularStrength,  100);  // Apply shininess factor
    vec3 specular = specularStrength * lightColor;  // Calculate specular contribution

    lighting = (ambientColor * .8) + (diffuse * 1) + (specular * 100);

    // Model Color
    vec3 modelColor = vec3(0.0471, 0.3882, 0.5882);

    // Final color
    vec3 color = modelColor * lighting ;

    // Output final color
    FragColor = vec4(color, 1.0);

    
    
}

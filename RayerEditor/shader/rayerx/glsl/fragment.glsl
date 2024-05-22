#version 450 core



uint NoTextureMaps = 0u;
uint AlbedoMap = 1u;
uint NormalMap = 2u;

uint textureMaps = NoTextureMaps | AlbedoMap | NormalMap;

in vec3 Normal;
in mat4 ViewMatrix;
in vec2 textureCordinates;
in flat int _id;

out vec4 FragColor;
layout(location = 1) out int id;

// Material types
uniform bool u_IsBasic;
uniform bool u_IsPBR;

// Texture maps flags
uniform uint texFlags;

// Model color uniform
uniform vec4 modelColor;

// Diffuse and normal texture uniforms
uniform sampler2D u_DiffuseMap;
uniform sampler2D u_NormalMap;



// Function to decode normal map
vec3 decodeNormal(vec3 encodedNormal) {
    vec3 normal = encodedNormal * 2.0 - 1.0; // Convert from [0, 1] to [-1, 1]
    return normalize(normal); // Normalize the vector
}

void main() {
    // Ambient color
    vec3 ambientColor = vec3(1.0);

    // Default normal
    vec3 normal = normalize(Normal);

    // If PBR, use the normal map
    if (u_IsPBR && (texFlags & NormalMap) != NoTextureMaps) {
        vec3 sampledNormal = texture(u_NormalMap, textureCordinates).rgb;
        normal = decodeNormal(sampledNormal);
        
        // Transform normal to view space
        mat3 normalMatrix = transpose(inverse(mat3(ViewMatrix)));
        normal = normalize(normalMatrix * normal);
    }

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
    vec3 lighting = (ambientColor * 0.8) + (diffuse * 1.0);

    // Calculate specular
    vec3 viewDir = normalize(-vec3(ViewMatrix[3]));  // View direction is the opposite of the camera position in view space
    vec3 reflectDir = normalize(reflect(-lightDir, normal));    // Reflect light direction around the normal
    float specularStrength = max(0.0, dot(reflectDir, viewDir));  // Calculate the angle between the reflect direction and the view direction
    specularStrength = pow(specularStrength, 100.0);  // Apply shininess factor
    vec3 specular = specularStrength * lightColor;  // Calculate specular contribution

    // Combine all lighting components
    lighting = (ambientColor * 0.8) + (diffuse * 1.0) + (specular * 1.0);

    vec3 color;

    if (u_IsBasic) {
        // Use model color directly if basic material
        color = vec3(modelColor) * lighting;

    } else if (u_IsPBR) {
        if ((texFlags & AlbedoMap) != NoTextureMaps) {
            vec4 texColor = texture(u_DiffuseMap, textureCordinates);
            color = vec3(texColor) * lighting;
        } else {
            // Use model color if no AlbedoMap is used
            color = vec3(modelColor) * lighting;
        }
    }

    // Output final color
    FragColor = vec4(color, 1.0);

    id = int(_id);
}

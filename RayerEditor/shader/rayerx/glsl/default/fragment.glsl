#version 450 core

uint NoTextureMaps = 0u;
uint AlbedoMap = 1u;
uint NormalMap = 2u;

uint textureMaps = NoTextureMaps | AlbedoMap | NormalMap;

in vec3 Normal;
in mat4 ViewMatrix;
in vec2 textureCordinates;
in flat int _id;

in vec3 fragPosWorldSpace;

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

// Directional light uniforms
struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float intensity;
};

#define MAX_DIRECTIONAL_LIGHTS 1
uniform DirectionalLight u_DirectionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform int u_NumDirectionalLights;

// Point light uniforms
struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
    float constant;
    float linear;
    float quadratic;
};

#define MAX_POINT_LIGHTS 10
uniform PointLight u_PointLights[MAX_POINT_LIGHTS];
uniform int u_NumPointLights;

// Function to decode normal map
vec3 decodeNormal(vec3 encodedNormal) {
    vec3 normal = encodedNormal * 2.0 - 1.0; // Convert from [0, 1] to [-1, 1]
    return normalize(normal); // Normalize the vector
}

// Calculate directional light contribution
vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
    vec3 directionalLightDir = normalize(light.direction);
    float directionalDiffuseStrength = max(0.0, dot(directionalLightDir, normal));
    vec3 directionalDiffuse = directionalDiffuseStrength * light.color * light.intensity;

    vec3 directionalReflectDir = normalize(reflect(-directionalLightDir, normal));  // Reflect light direction around the normal
    float directionalSpecularStrength = max(0.0, dot(directionalReflectDir, viewDir));  // Calculate the angle between the reflect direction and the view direction
    directionalSpecularStrength = pow(directionalSpecularStrength, 100.0);  // Apply shininess factor
    vec3 directionalSpecular = directionalSpecularStrength * light.color * light.intensity;  // Calculate specular contribution

    return (directionalDiffuse * 1.0) + (directionalSpecular * 1.0);
}

// Calculate point light contribution
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPosViewSpace) {

    
    vec3 lightPosViewSpace = (ViewMatrix * vec4(light.position, 1.0)).xyz;
    vec3 lightDir = normalize(lightPosViewSpace - fragPosViewSpace);  // Direction from fragment to light
    float distance = length(lightPosViewSpace - fragPosViewSpace);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Diffuse
    float diffuseStrength = max(0.0, dot(lightDir, normal));
    vec3 diffuse = diffuseStrength * light.color * light.intensity * attenuation;

    // Specular
    vec3 viewDir = normalize(-fragPosViewSpace);  // View direction is from the fragment to the camera
    vec3 reflectDir = reflect(-lightDir, normal);  // Reflect light direction around the normal
    float specularStrength = max(0.0, dot(reflectDir, viewDir));
    specularStrength = pow(specularStrength, 2);  // Use material shininess factor
    vec3 specular = specularStrength * light.color * light.intensity * attenuation;

    return diffuse + specular;
}

void main() {

    
    vec3 fragmentPosViewSpace = vec3(ViewMatrix * vec4(fragPosWorldSpace, 1.0));
    vec3 ambientColor = vec3(1.0);
    vec3 normal = normalize(Normal);

    // If PBR, use the normal map
    if (u_IsPBR && (texFlags & NormalMap) != NoTextureMaps) {
        vec3 sampledNormal = texture(u_NormalMap, textureCordinates).rgb;
        normal = decodeNormal(sampledNormal);
        
        // Transform normal to view space
        mat3 normalMatrix = transpose(inverse(mat3(ViewMatrix)));
        normal = normalize(normalMatrix * normal);
    }

    // Initialize lighting with ambient component
    vec3 lighting = ambientColor * 0.8;
    vec3 viewDir = normalize(-vec3(ViewMatrix[3]));  // View direction is the opposite of the camera position in view space

    // Directional lights calculation
    for (int i = 0; i < u_NumDirectionalLights; ++i) {
        lighting += calculateDirectionalLight(u_DirectionalLights[i], normal, viewDir);
    }

    // Point lights calculation
    for (int i = 0; i < u_NumPointLights; ++i) {
        lighting += calculatePointLight(u_PointLights[i], normal, fragmentPosViewSpace);
    }

   

    // Ensure lighting is not zero (fallback to ambient if no lights are present)
    if (u_NumDirectionalLights == 0 && u_NumPointLights == 0) {
        lighting = ambientColor * 0.8;
    }

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

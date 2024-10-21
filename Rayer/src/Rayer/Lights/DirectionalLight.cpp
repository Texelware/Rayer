#include "DirectionalLight.h"


//Component header
#include <Rayer/Component/TransformComponent.h>
#include <Rayer/Component/LightComponent.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Rayer {

	DirectionalLight::DirectionalLight(const std::string& name , const int entity_id) : Light(LightType::Directional, name , entity_id) {
	
		AddComponent(new TransformComponent(modelMatrix));
		AddComponent(new LightComponent(this));
		
	}

	void DirectionalLight::CalculateDirection() {

		
		glm::vec3 originalLightDirection = glm::vec3(0.0f, -1.0f, 0.0f); // Original light direction

		// Extract the rotation part of the model matrix (the upper-left 3x3 part)
		glm::mat3 rotationMatrix = glm::mat3(modelMatrix);

		// Transform the original light direction by the rotation matrix
		glm::vec3 transformedLightDirection = rotationMatrix * originalLightDirection;

		// Normalize the transformed light direction
		transformedLightDirection = glm::normalize(transformedLightDirection);
		
		lightProps.direction = transformedLightDirection;

	}

	glm::mat4 DirectionalLight::GetLightSpaceMatrix() {

		glm::mat4 lightProjection = GetProjectionMatrix(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 75.0f);

		glm::vec3 lightPosition = glm::vec3(modelMatrix[3]);

		glm::mat4 lightView = glm::lookAt(lightPosition, lightProps.direction, glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 lightSpaceMatrix = lightProjection * lightView;

		return lightSpaceMatrix;

	}

	glm::mat4 DirectionalLight::GetProjectionMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane) const {

		return glm::ortho(left, right, bottom, top, nearPlane, farPlane);
	}


}
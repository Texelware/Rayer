#include "SpotLight.h"


//Component header
#include <Rayer/Component/TransformComponent.h>
#include <Rayer/Component/LightComponent.h>

namespace Rayer {

	SpotLight::SpotLight(const std::string& name) : Light(LightType::Spot , name) {
		
		//Adding components
		AddComponent(new TransformComponent(modelMatrix));
		AddComponent(new LightComponent(this));

	}


	void SpotLight::CalculatePosition() {

		lightProps.position = glm::vec3(modelMatrix[3]);

	}

	void SpotLight::CalculateDirection() {
		// Default direction vector (e.g., pointing along negative Z-axis)
		glm::vec3 defaultDirection = glm::vec3(0.0f, -1.0f, 0.0f);

		// Extract the rotational part of the model matrix
		glm::mat3 rotationMatrix = glm::mat3(modelMatrix);

		// Transform the default direction vector by the rotation matrix
		lightProps.direction = rotationMatrix * defaultDirection;
	}

	void SpotLight::CalculateSpread() {

		lightProps.cutOff = glm::cos(glm::radians(lightProps.spread));

	}
}
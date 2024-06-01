#include "PointLight.h"

//Component header
#include <Rayer/Component/TransformComponent.h>
#include <Rayer/Component/LightComponent.h>

namespace Rayer {


	PointLight::PointLight(const std::string& name) : Light(LightType::Point, name) {
	
		AddComponent(new TransformComponent(modelMatrix));
		AddComponent(new LightComponent(this));
	
	}

	void PointLight::CalculatePosition() {

		lightProps.position = glm::vec3(modelMatrix[3]);

	}

}
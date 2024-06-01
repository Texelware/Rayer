#include "SkyLight.h"
#include <Rayer/Component/SkyLightComponent.h>
#include <Rayer/Component/TransformComponent.h>

namespace Rayer {

	SkyLight::SkyLight(std::string name) : Light(LightType::SkyLight, name) {
		
		AddComponent(new TransformComponent(modelMatrix));
		AddComponent(new SkyLightComponent());

	}


}
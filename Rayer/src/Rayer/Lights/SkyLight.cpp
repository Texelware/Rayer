#include "SkyLight.h"
#include <Rayer/Component/SkyLightComponent.h>
#include <Rayer/Component/TransformComponent.h>

namespace Rayer {

	SkyLight::SkyLight(std::string name , const int entity_id) : Light(LightType::SkyLight, name , entity_id) {
		
		AddComponent(new TransformComponent(modelMatrix));
		AddComponent(new SkyLightComponent());

	}


}
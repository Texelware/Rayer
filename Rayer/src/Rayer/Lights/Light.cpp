#include "Light.h"
#include <Rayer/Scene/Scene.h>

namespace Rayer {


	Light::Light(LightType type, std::string name) : Entity(name, Scene::nextEntityID, EntityType::Light), m_type{type} {}


}
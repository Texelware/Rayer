#include "Light.h"
#include <Rayer/Scene/Scene.h>

namespace Rayer {


	Light::Light(LightType type, std::string name , const int entity_id) : Entity(name, entity_id, EntityType::Light), m_type{type} {}


}
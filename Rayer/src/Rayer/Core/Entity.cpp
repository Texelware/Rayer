#include "Entity.h"
#include <Rayer/Scene/Scene.h>

namespace Rayer {


	Entity::Entity(const std::string& _name, int _id ,  EntityType _type) : name(_name), type(_type), id(_id) {

		Scene::nextEntityID++;

	}

}
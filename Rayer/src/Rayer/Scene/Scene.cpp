#include "Scene.h"

namespace Rayer {

	std::string Scene::selectedEntityName{};

	int Scene::selectedEntityID = -1;

	int Scene::nextEntityID = 0;

	void Scene::AddEntity(Ref<Entity>& entity) {

		m_Entities.push_back(std::move(entity));
	
	}

	void Scene::RemoveEntity(int entityID) {

		if (!m_Entities.empty()) {

			for (auto it = m_Entities.begin(); it != m_Entities.end(); it++) {

				Ref<Entity> entity = *it;

				if (entity->GetEntityID() == Scene::selectedEntityID) {

					m_Entities.erase(it);
					break;
				}
			}

		}

	}

}
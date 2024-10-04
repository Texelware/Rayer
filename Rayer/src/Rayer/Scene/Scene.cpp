#include "Scene.h"

namespace Rayer {

	int Scene::directionalLightCount = 0;
	int Scene::pointLightCount = 0;
	int Scene::spotLightCount = 0;

	Scene::Scene() {

		

		sceneSerializer = std::make_unique<SceneSerializer>(this);


	}

	
	
	Ref<Entity> Scene::directionalLight = nullptr;

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

	void Scene::ClearScene() {

		//clear all entities
		m_Entities.clear();

		//make the next entity id to 0
		nextEntityID = 0;

		//reset selected entity id and name
		selectedEntityID = -1;
		selectedEntityName.clear();

		//reset directional light
		directionalLight = nullptr;

		directionalLightCount = 0;
		pointLightCount = 0;
		spotLightCount = 0;

	}

}
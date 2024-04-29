#include "Scene.h"

namespace Rayer {

	std::string Scene::selectedObjectName{};

	void Scene::AddModel(Ref<Model>& model) {

		m_Models.push_back(std::move(model));
	
	}

}
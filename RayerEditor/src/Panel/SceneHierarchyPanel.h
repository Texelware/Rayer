#pragma once
#include <Rayer.h>

#include <filesystem>


#include <Rayer/Lights/SkyLight.h>
#include <Rayer/Lights/DirectionalLight.h>
#include <Rayer/Lights/PointLight.h>

namespace Rayer {

	struct PrimitiveObject {

		std::string name;
		std::filesystem::path _filePath;

	};

	struct SceneLight {

		std::string name;
		LightType lightType;

	};

	class SceneHierarchyPanel {


	public:
		SceneHierarchyPanel(const Ref<Scene>& scene = Application::Get().GetScene());
		void OnImGuiRender();

		void AddLight(LightType type);

		void AddNewModel(const std::filesystem::path& filepath);

	private:

		static bool showSceneHierarchyPanel;
		static bool showScenePropertyPanel;

		Ref<Scene> m_Scene;

		std::vector<PrimitiveObject> m_PrimitiveObjects;
		std::vector<SceneLight> m_SceneLights;

	};

	

}
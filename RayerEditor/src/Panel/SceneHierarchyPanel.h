#pragma once
#include <Rayer.h>

namespace Rayer {


	class SceneHierarchyPanel {


	public:
		SceneHierarchyPanel(const Ref<Scene>& scene = Application::Get().GetScene());
		void OnImGuiRender();

	private:

		static bool showSceneHierarchyPanel;
		static bool showScenePropertyPanel;

		Ref<Scene> m_Scene;

	};

	

}
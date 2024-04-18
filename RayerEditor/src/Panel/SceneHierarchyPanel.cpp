#include <imgui.h>

#include <Panel/SceneHierarchyPanel.h>


namespace Rayer {

	bool SceneHierarchyPanel::showSceneHierarchyPanel = true;
	bool SceneHierarchyPanel::showScenePropertyPanel = true;

	void SceneHierarchyPanel::OnImGuiRender() {

		if (showSceneHierarchyPanel) {

			ImGui::Begin("Scene Hierarchy", &showSceneHierarchyPanel);

			ImGui::End();

		}

		if (showScenePropertyPanel) {

			ImGui::Begin("Properties", &showScenePropertyPanel);

			ImGui::End();

		}

	}

}
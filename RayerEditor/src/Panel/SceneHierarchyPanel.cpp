#include <imgui.h>

#include <Panel/SceneHierarchyPanel.h>


namespace Rayer {

	bool SceneHierarchyPanel::showSceneHierarchyPanel = true;
	bool SceneHierarchyPanel::showScenePropertyPanel = true;


	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene) : m_Scene{scene} {}

	void SceneHierarchyPanel::OnImGuiRender() {

        if (showSceneHierarchyPanel) {
            ImGui::Begin("Scene Hierarchy", &showSceneHierarchyPanel);

            for (auto it = m_Scene->getModelIteratorBeginC(); it != m_Scene->getModelIteratorEndC(); ++it) {
                const Ref<Model>& model = *it;

                // Check if the model is selected or not
                bool isSelected = (Scene::selectedObjectName == model->GetModelName());

                // Render selectable item
                if (ImGui::Selectable(model->GetModelName().c_str(), &isSelected)) {
                    // If the item is clicked, update the selected object name
                    Scene::selectedObjectName = model->GetModelName();
                }
            }

            ImGui::End();
        }

		if (showScenePropertyPanel) {

			ImGui::Begin("Properties", &showScenePropertyPanel);

			ImGui::End();

		}

	}

}
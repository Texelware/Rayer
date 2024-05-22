#include <imgui.h>

#include <Panel/SceneHierarchyPanel.h>
#include <Rayer/Log/Logger.h>

namespace Rayer {

    

	bool SceneHierarchyPanel::showSceneHierarchyPanel = true;
	bool SceneHierarchyPanel::showScenePropertyPanel = true;


	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene ) : m_Scene{scene} {}

	void SceneHierarchyPanel::OnImGuiRender() {

        if (showSceneHierarchyPanel) {

            ImGui::Begin("Scene Hierarchy", &showSceneHierarchyPanel);

            
            for (auto it = m_Scene->getEntityIteratorBeginC(); it != m_Scene->getEntityIteratorEndC(); ++it) {
                const Ref<Entity>& entity = *it;

                // Check if the model is selected or not
                bool isSelected = (Scene::selectedEntityID == entity->GetEntityID());

                // Render selectable item
                if (ImGui::Selectable(entity->GetEntityName().c_str(), &isSelected)) {

                    // If the item is clicked, update the selected entity name
					Scene::selectedEntityID = entity->GetEntityID();
                    Scene::selectedEntityName = entity->GetEntityName();
                }


               
            }

            if (ImGui::IsWindowHovered()) {

                //Delete entities when window is hovered and delete key is pressed 
                if (Input::IsKeyPressed(Key::Delete)) {

                    if (Scene::selectedEntityID != -1) {

                        Application::Get().GetScene()->RemoveEntity(Scene::selectedEntityID);

                    }

                }
            }

            // Right-click on blank space
            if (ImGui::BeginPopupContextWindow(0, 1))
            {
                

                  if(ImGui::BeginMenu("Create object")) {

                      if(ImGui::MenuItem("Cube")) {

					    std::cout << "Cube" << std::endl;

                      }

                      ImGui::EndMenu();

                  }
                
                    

                ImGui::EndPopup();
            }


            ImGui::End();
        }

		if (showScenePropertyPanel) {

			ImGui::Begin("Properties", &showScenePropertyPanel);

            for (auto it = m_Scene->getEntityIteratorBeginC(); it != m_Scene->getEntityIteratorEndC(); ++it) {

                const Ref<Entity>& entity = *it;

                // Check if the model is selected or not
                bool isSelected = (entity->GetEntityID() == Scene::selectedEntityID);
                
                if (isSelected) {

                    for (auto component_it = entity->beginComponentIteratorC(); component_it != entity->endComponentIteratorC(); ++component_it) {

                        
                        (*component_it)->OnRender();
                        

                    }

                    if (ImGui::Button("+ADD", ImVec2(350, 0))) {

						ImGui::OpenPopup("AddComponent");

                    }
                    
                    if (ImGui::BeginPopup("AddComponent")) {


                        if (entity->GetEntityType() == EntityType::Model) {

                            if (ImGui::MenuItem("Material")) {

                                if (entity->HasComponent(ComponentType::MaterialComponent))
                                {

                                    std::cout << "Already have a material component" << std::endl;
                                    LogManager::Get()->AddLog({ LogLevel::LOG_LEVEL_WARN , std::string(entity->GetEntityName() + " Already have a material component")});
                                }
                                else {
                                    entity->AddComponent(new MaterialComponent());
                                }
                            }
                            

                        }



                        ImGui::EndPopup();
                    }
                }

                


            }

			ImGui::End();

		}

	}

}
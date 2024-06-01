#include <imgui.h>

#include <Panel/SceneHierarchyPanel.h>
#include <Rayer/Log/Logger.h>



#include <Rayer/Filesystem/FileSystem.h>

namespace Rayer {

   
	bool SceneHierarchyPanel::showSceneHierarchyPanel = true;
	bool SceneHierarchyPanel::showScenePropertyPanel = true;


    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene) : m_Scene{ scene }, m_PrimitiveObjects{

		//Add your primitives here
        {"Cube" , RayerFileSystem::_currentWorkingPath.string() + "/assets/primitives/Cube.obj"},
        {"Cylinder" , RayerFileSystem::_currentWorkingPath.string() + "/assets/primitives/Cylinder.obj"},
        {"Cone" , RayerFileSystem::_currentWorkingPath.string() + "/assets/primitives/Cone.obj"},
        {"Sphere" , RayerFileSystem::_currentWorkingPath.string() + "/assets/primitives/Sphere.obj"},
        {"Torus" , RayerFileSystem::_currentWorkingPath.string() + "/assets/primitives/Torus.obj"},
        {"Plane" , RayerFileSystem::_currentWorkingPath.string() + "/assets/primitives/Plane.obj"}

    },

    m_SceneLights{


        //Add your scene lights here
        {"Skylight" , LightType::SkyLight},
		{"Directional Light" , LightType::Directional},
		{"Point Light" , LightType::Point}
         
    }

    {}

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




                        if (Scene::selectedEntityID != -1) {

                            // Get the iterators for the models in the scene
                            auto entityBegin = Application::Get().GetScene()->getEntityIteratorBeginC();
                            auto entityEnd = Application::Get().GetScene()->getEntityIteratorEndC();

                            if (entityBegin != entityEnd) {
                                // Iterate over the models in the scene and draw each one
                                for (auto entityIt = entityBegin; entityIt != entityEnd; ++entityIt) {

                                    const Ref<Entity> entity = *entityIt;

                                    if (entity->GetEntityID() == Scene::selectedEntityID) {

                                        if (entity->GetEntityType() == EntityType::Light) {

                                            auto light = std::dynamic_pointer_cast<Light>(entity);

                                            if (light->GetLightType() == LightType::Directional && Scene::directionalLightCount != 0) {

                                                Scene::directionalLightCount--;

                                            }

                                            if (light->GetLightType() == LightType::Point && Scene::pointLightCount != 0) {

                                                Scene::pointLightCount--;
                                            }

                                        }
                                    }
                                }

                            }

                            Application::Get().GetScene()->RemoveEntity(Scene::selectedEntityID);

                        }

                    }

                }
            }

            // Right-click on blank space
            if (ImGui::BeginPopupContextWindow(0, 1))
            {
                

                  if(ImGui::BeginMenu("Object")) {

                      

                      for (auto it = m_PrimitiveObjects.begin(); it != m_PrimitiveObjects.end(); ++it) {

                          if (ImGui::MenuItem(it->name.c_str())) {

                             
                              if (!it->_filePath.empty()) {

                                  AddNewModel(it->_filePath);
                              }

                          }


                      }
						  


                      ImGui::EndMenu();

                  }

                  
                  if (ImGui::BeginMenu("Lights")) {

                      for (auto it = m_SceneLights.begin(); it < m_SceneLights.end(); ++it) {

                          if (ImGui::MenuItem(it->name.c_str())) {

                              AddLight(it->lightType);

                          }

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


    void SceneHierarchyPanel::AddLight(LightType type) {


        //Adding skylight
        if (type == LightType::SkyLight) {

            for (auto it = m_Scene->getEntityIteratorBeginC(); it != m_Scene->getEntityIteratorEndC(); ++it) {

                const Ref<Entity>& entity = *it;

                if (entity->GetEntityType() == EntityType::Light) {

                    if (std::dynamic_pointer_cast<Light>(entity)->GetLightType() == LightType::SkyLight) {
                        
                        LogManager::Get()->AddLog({ LogLevel::LOG_LEVEL_ERROR , std::string("Rayer support only one skylight") });
						return;
                    }

                }

            }

            Ref<Entity> skylight = CreateRef<SkyLight>("Skylight");

			
            Scene::selectedEntityID = skylight->GetEntityID();

            m_Scene->AddEntity(skylight);

            

        }


        else if (type == LightType::Point) {

            if (Scene::pointLightCount < NUM_MAX_POINT_LIGHT) {
                std::string entityName = "Point Light";
                auto beginIt = Application::Get().GetScene()->getEntityIteratorBeginC();
                auto endIt = Application::Get().GetScene()->getEntityIteratorEndC();

                // Check if the model name already exists
                int count = 1;
                std::string originalName = entityName;
                while (std::find_if(beginIt, endIt, [&](const Ref<Entity>& entity) { return entity->GetEntityName() == entityName; }) != endIt) {
                    entityName = originalName + "(" + std::to_string(count) + ")";
                    count++;
                }

                Ref<Entity> light = CreateRef<PointLight>(entityName);
                Scene::selectedEntityID = light->GetEntityID();

                // Adding a new point light into the scene
                Application::Get().GetScene()->AddEntity(light);

                Scene::pointLightCount++;

               

            }

            else {
                
                LogManager::Get()->AddLog({ LogLevel::LOG_LEVEL_ERROR , std::string("Rayer doesn't support more than " +std::to_string(NUM_MAX_POINT_LIGHT) + " point lights")});
                return;

            }
            

        }

        else if (type == LightType::Directional) {


            if (Scene::directionalLightCount < NUM_MAX_DIRECTIONAL_LIGHT) {

                std::string entityName = "Directional Light";
                auto beginIt = Application::Get().GetScene()->getEntityIteratorBeginC();
                auto endIt = Application::Get().GetScene()->getEntityIteratorEndC();

                // Check if the model name already exists
                int count = 1;
                std::string originalName = entityName;
                while (std::find_if(beginIt, endIt, [&](const Ref<Entity>& entity) { return entity->GetEntityName() == entityName; }) != endIt) {
                    entityName = originalName + "(" + std::to_string(count) + ")";
                    count++;
                }

                Ref<Entity> light = CreateRef<DirectionalLight>(entityName);

                Scene::directionalLight = light;
                Scene::selectedEntityID = light->GetEntityID();
                // Adding a new point light into the scene
                Application::Get().GetScene()->AddEntity(light);


                //Increasing the count
                Scene::directionalLightCount++;

                

            }

            else {

                LogManager::Get()->AddLog({ LogLevel::LOG_LEVEL_ERROR , std::string("Rayer doesn't support more than " + std::to_string(NUM_MAX_DIRECTIONAL_LIGHT) + " directional lights") });
                return;

            }

        }

        else {

            #ifdef RAYER_DEBUG
            
			    std::cout << "Light type is not supported or not added yet !" << std::endl;

            #endif // RAYER_DEBUG


        }

    }


    void SceneHierarchyPanel::AddNewModel(const std::filesystem::path& filepath) {

      
        std::string entityName = filepath.stem().string();
        auto beginIt = Application::Get().GetScene()->getEntityIteratorBeginC();
        auto endIt = Application::Get().GetScene()->getEntityIteratorEndC();

        // Check if the model name already exists
        int count = 1;
        std::string originalName = entityName;
        while (std::find_if(beginIt, endIt, [&](const Ref<Entity>& entity) { return entity->GetEntityName() == entityName; }) != endIt) {
            entityName = originalName + "(" + std::to_string(count) + ")";
            count++;
        }

        Ref<Entity> model = CreateRef<Model>(entityName, Scene::nextEntityID, EntityType::Model, filepath);
        //Scene::nextEntityID++;

        if (std::dynamic_pointer_cast<Model>(model)->IsReadSuccessful()) {
            Scene::selectedEntityID = model ->GetEntityID();
            // Adding a new model into the current scene
            Application::Get().GetScene()->AddEntity(model);
           
        }

        else {


        }


    }

}
#include "MaterialComponent.h"
#include <imgui.h>
#include <Rayer/Filesystem/FileSystem.h>
#include <Rayer/Log/Logger.h>
#include <glm/gtc/type_ptr.hpp>

namespace Rayer {

	

	MaterialComponent::MaterialComponent() : Component(ComponentType::MaterialComponent) {
		
		m_platformUtils = PlatformUtils::Create();
		

		std::string absolute_path = RayerFileSystem::_currentWorkingPath.string() + "/assets/textures/checkerboard.png";


		checkerboard_texture = Texture2D::Create(absolute_path);

		m_material = CreateRef<PBR_Material>();
		

		
	}

	MaterialComponent::MaterialComponent(Ref<Material> material) : Component(ComponentType::MaterialComponent) {

		m_platformUtils = PlatformUtils::Create();


		std::string absolute_path = RayerFileSystem::_currentWorkingPath.string() + "/assets/textures/checkerboard.png";


		checkerboard_texture = Texture2D::Create(absolute_path);

		m_material = material;



	}


	void MaterialComponent::OnRender() {


		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed |
			ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

		if (ImGui::TreeNodeEx("Material", treeNodeFlags)) {

			
			ImGui::SetNextItemWidth(100);
			// Begin the combo box
			if (ImGui::BeginCombo("Material Type", comboPreviewValue.c_str())) {

				for (int n = 0; n < items.size(); n++) {

					const bool isSelected = (currentItem == n);
					if (ImGui::Selectable(items[n].c_str(), isSelected)) {
						currentItem = n; // Update current item if selected
						comboPreviewValue = items[currentItem]; // Update the preview value

						if (items[n] == "PBR") {

							if (m_material->GetMaterialType() != MaterialType::PBR) {

								m_material = CreateRef<PBR_Material>();

							}

						}
						
						else if (items[n] == "BASIC") {

							if (m_material->GetMaterialType() != MaterialType::BASIC) {

								m_material = CreateRef<BASIC_Material>();

							}

						}

					}
					if (isSelected) {
						ImGui::SetItemDefaultFocus(); // Ensure the currently selected item is always focused
					}
				}
				ImGui::EndCombo();
			}
		

			ImGui::Separator();

			// For the albedo map for PBR materials
			if (m_material->GetMaterialType() == MaterialType::PBR) {

				if (std::dynamic_pointer_cast<PBR_Material>(m_material)->GetTextureAvailabilityStatus().has_albedo) {

					ImGui::PushID("AlbedoButtonPresentTexture");
					if (ImGui::ImageButton(ImTextureID(std::dynamic_pointer_cast<PBR_Material>(m_material)->GetMaterialMaps()->albedo->GetRendererID()), ImVec2(50, 50))) {

						fs::path _path = m_platformUtils->OpenFileDialog("*.png,*.jpg");

						if (!_path.empty() && (_path.extension() == ".jpg" || _path.extension() == ".png")) {

							Ref<Texture2D> _texture = Texture2D::Create(_path);

							std::dynamic_pointer_cast<PBR_Material>(m_material)->Update(_texture, MapType::Albedo , _path);

						}

						else {

							LogManager::Get()->AddLog({ LogLevel::LOG_LEVEL_ERROR , std::string("Failed to add texture! Possible reasons: Path does not exist or file format is incorrect or not supported.") });

						}

					}

					ImGui::SameLine();
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
					ImGui::Text("Albedo");

					ImGui::SameLine();
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 180);
					if (ImGui::Button("x")) {

						if (std::dynamic_pointer_cast<PBR_Material>(m_material)->GetMaterialMaps()->albedo != nullptr) {

							std::dynamic_pointer_cast<PBR_Material>(m_material)->GetTextureAvailabilityStatus().has_albedo = false;
							std::dynamic_pointer_cast<PBR_Material>(m_material)->GetMaterialMaps()->albedo = nullptr;

						}

					}
					ImGui::PopStyleColor();

					ImGui::PopID();

					ImGui::Separator();
				}

				else {

					ImGui::PushID("AlbedoButtonAbsentTexture");
					if (ImGui::ImageButton(ImTextureID(checkerboard_texture->GetRendererID()), ImVec2(50, 50))) {

						fs::path _path = m_platformUtils->OpenFileDialog("*.png,*.jpg");

						if (!_path.empty() && (_path.extension() == ".jpg" || _path.extension() == ".png")) {

							Ref<Texture2D> _texture = Texture2D::Create(_path);

							std::dynamic_pointer_cast<PBR_Material>(m_material)->Update(_texture, MapType::Albedo, _path);

						}

						else {

							LogManager::Get()->AddLog({ LogLevel::LOG_LEVEL_ERROR , std::string("Failed to add texture! Possible reasons: Path does not exist or file format is incorrect or not supported.") });

						}

					}

					

					ImGui::SameLine();
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
					ImGui::Text("Albedo");

					ImGui::SameLine();
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 180);
					if (ImGui::Button("x")) {

						if (std::dynamic_pointer_cast<PBR_Material>(m_material)->GetMaterialMaps()->albedo != nullptr) {

							std::dynamic_pointer_cast<PBR_Material>(m_material)->GetTextureAvailabilityStatus().has_albedo = false;
							std::dynamic_pointer_cast<PBR_Material>(m_material)->GetMaterialMaps()->albedo = nullptr;

						}

					}
					ImGui::PopStyleColor();

					ImGui::PopID();
					
					ImGui::Separator();
				}

				// For normal map
				if (std::dynamic_pointer_cast<PBR_Material>(m_material)->GetTextureAvailabilityStatus().has_normal) {

					ImGui::PushID("NormalButtonPresentTexture");
					if (ImGui::ImageButton(ImTextureID(std::dynamic_pointer_cast<PBR_Material>(m_material)->GetMaterialMaps()->normal->GetRendererID()), ImVec2(50, 50))) {

						fs::path _path = m_platformUtils->OpenFileDialog("*.png,*.jpg");

						if (!_path.empty() && (_path.extension() == ".jpg" || _path.extension() == ".png")) {

							Ref<Texture2D> _texture = Texture2D::Create(_path);

							std::dynamic_pointer_cast<PBR_Material>(m_material)->Update(_texture, MapType::Normal , _path);

						}

					}
					ImGui::SameLine();
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
					ImGui::Text("Normal");

					ImGui::SameLine();
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 180);
					if (ImGui::Button("x")) {

						if (std::dynamic_pointer_cast<PBR_Material>(m_material)->GetMaterialMaps()->normal != nullptr) {

							std::dynamic_pointer_cast<PBR_Material>(m_material)->GetTextureAvailabilityStatus().has_normal = false;
							std::dynamic_pointer_cast<PBR_Material>(m_material)->GetMaterialMaps()->normal = nullptr;

						}

					}
					ImGui::PopStyleColor();

					ImGui::PopID();

					ImGui::Separator();
				}

				else {

					ImGui::PushID("NormalButtonAbsentTexture");
					if (ImGui::ImageButton(ImTextureID(checkerboard_texture->GetRendererID()), ImVec2(50, 50))) {

						fs::path _path = m_platformUtils->OpenFileDialog("*.png,*.jpg");

						if (!_path.empty() && (_path.extension() == ".jpg" || _path.extension() == ".png")) {

							Ref<Texture2D> _texture = Texture2D::Create(_path);

							std::dynamic_pointer_cast<PBR_Material>(m_material)->Update(_texture, MapType::Normal , _path);

						}

						else {

							LogManager::Get()->AddLog({ LogLevel::LOG_LEVEL_ERROR , std::string("Failed to add texture! Possible reasons: Path does not exist or file format is incorrect or not supported.") });

						}

					}



					ImGui::SameLine();
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
					ImGui::Text("Normal");
					
					ImGui::SameLine();
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 180);
					if (ImGui::Button("x")) {

						if (std::dynamic_pointer_cast<PBR_Material>(m_material)->GetMaterialMaps()->normal != nullptr) {
							
							std::dynamic_pointer_cast<PBR_Material>(m_material)->GetTextureAvailabilityStatus().has_normal = false;
							std::dynamic_pointer_cast<PBR_Material>(m_material)->GetMaterialMaps()->normal = nullptr;

						}

						else {

							LogManager::Get()->AddLog({ LogLevel::LOG_LEVEL_ERROR , std::string("Failed to add texture! Possible reasons: Path does not exist or file format is incorrect or not supported.") });


						}

					}

					ImGui::PopStyleColor();

					ImGui::PopID();

					ImGui::Separator();

				}



				
			}

			else if (m_material->GetMaterialType() == MaterialType::BASIC) {

				glm::vec4& _color = std::dynamic_pointer_cast<BASIC_Material>(m_material)->GetColor();

				ImVec4 buttonColor = ImVec4(_color.x, _color.y, _color.z, _color.w);

				// Color Button
				if (ImGui::ColorButton("ColorButton", buttonColor, ImGuiColorEditFlags_NoAlpha, ImVec2(50, 50))) {
					showColorPicker = !showColorPicker; // Toggle the visibility of the color picker
				}

				ImGui::SameLine();
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 13);
				ImGui::Text("Base color");

				if (showColorPicker) {
					ImGui::SetNextWindowPos(ImVec2(ImGui::GetCursorScreenPos().x + 100 , ImGui::GetCursorScreenPos().y - 400), ImGuiCond_FirstUseEver);
					ImGui::Begin("Color Picker", &showColorPicker, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize); // Remove ImGuiWindowFlags_NoMove if present
					ImGui::ColorPicker4("Color Picker", glm::value_ptr(_color));
					ImGui::End();
					
				}


			}

			ImGui::TreePop();
			ImGui::Separator();

		}
	}
	void MaterialComponent::OnUpdate() {


		


	}


}
#include "LightComponent.h"
#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

namespace Rayer {

	LightComponent::LightComponent(Light* light) : Component(ComponentType::LightComponent) ,  m_Light(light), m_LightType(light->GetLightType()) {
		

	}

	void LightComponent::OnUpdate() {
		
	}

	void LightComponent::OnRender() {

		

			const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed |
				ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

			if (ImGui::TreeNodeEx("Light", treeNodeFlags)) {

				if (m_LightType == LightType::Directional) {

					glm::vec3& _color = dynamic_cast<DirectionalLight*>(m_Light)->GetLightProperties().color;
					float* intensity = &dynamic_cast<DirectionalLight*>(m_Light)->GetLightProperties().intensity;
					

					ImVec4 buttonColor = ImVec4(_color.x, _color.y, _color.z , 1.0);

				
					// Color Button
					if (ImGui::ColorButton("ColorButton", buttonColor, ImGuiColorEditFlags_NoAlpha, ImVec2(50, 50))) {
						showColorPicker = !showColorPicker; // Toggle the visibility of the color picker
					}

					ImGui::SameLine();
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 13);
					ImGui::Text("Base color");

					if (showColorPicker) {
						ImGui::SetNextWindowPos(ImVec2(ImGui::GetCursorScreenPos().x + 100, ImGui::GetCursorScreenPos().y - 400), ImGuiCond_FirstUseEver);
						ImGui::Begin("Color Picker", &showColorPicker, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize); // Remove ImGuiWindowFlags_NoMove if present
						ImGui::ColorPicker3("Color Picker", glm::value_ptr(_color));
						
						ImGui::End();

					}

					ImGui::DragFloat("intensity", intensity, 0.1f, 0.0f, 1.0f);

				}

				else if (m_LightType == LightType::Point) {


					glm::vec3& _color = dynamic_cast<PointLight*>(m_Light)->GetLightProperties().color;
					float* intensity = &dynamic_cast<PointLight*>(m_Light)->GetLightProperties().intensity;


					ImVec4 buttonColor = ImVec4(_color.x, _color.y, _color.z, 1.0);


					// Color Button
					if (ImGui::ColorButton("ColorButton", buttonColor, ImGuiColorEditFlags_NoAlpha, ImVec2(50, 50))) {
						showColorPicker = !showColorPicker; // Toggle the visibility of the color picker
					}

					ImGui::SameLine();
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 13);
					ImGui::Text("Base color");

					if (showColorPicker) {
						ImGui::SetNextWindowPos(ImVec2(ImGui::GetCursorScreenPos().x + 100, ImGui::GetCursorScreenPos().y - 400), ImGuiCond_FirstUseEver);
						ImGui::Begin("Color Picker", &showColorPicker, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize); // Remove ImGuiWindowFlags_NoMove if present
						ImGui::ColorPicker3("Color Picker", glm::value_ptr(_color));

						ImGui::End();

					}

					ImGui::DragFloat("intensity", intensity, 0.1f, 0.0f, 1.0f);


				}


				else if (m_LightType == LightType::Spot) {


					glm::vec3& _color = dynamic_cast<SpotLight*>(m_Light)->GetLightProperties().color;
					float* intensity = &dynamic_cast<SpotLight*>(m_Light)->GetLightProperties().intensity;
					float* spread = &dynamic_cast<SpotLight*>(m_Light)->GetLightProperties().spread;


					ImVec4 buttonColor = ImVec4(_color.x, _color.y, _color.z, 1.0);


					// Color Button
					if (ImGui::ColorButton("ColorButton", buttonColor, ImGuiColorEditFlags_NoAlpha, ImVec2(50, 50))) {
						showColorPicker = !showColorPicker; // Toggle the visibility of the color picker
					}

					ImGui::SameLine();
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 13);
					ImGui::Text("Base color");

					if (showColorPicker) {
						ImGui::SetNextWindowPos(ImVec2(ImGui::GetCursorScreenPos().x + 100, ImGui::GetCursorScreenPos().y - 400), ImGuiCond_FirstUseEver);
						ImGui::Begin("Color Picker", &showColorPicker, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize); // Remove ImGuiWindowFlags_NoMove if present
						ImGui::ColorPicker3("Color Picker", glm::value_ptr(_color));

						ImGui::End();

					}

					ImGui::DragFloat("intensity", intensity, 0.1f, 0.0f, 1.0f);
					ImGui::DragFloat("spread", spread, 0.1f, 10.0f, 80.0f);


				}


				ImGui::TreePop();

			}

		

	}

}
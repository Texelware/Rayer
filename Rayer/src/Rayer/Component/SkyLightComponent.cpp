#include "SkyLightComponent.h"
#include <Rayer/Log/Logger.h>
#include <imgui.h>

namespace Rayer {

	SkyLightComponent::SkyLightComponent() : Component(ComponentType::SkyLightComponent) {
		
		platformUtils = PlatformUtils::Create();

		folderIcon = Texture2D::Create(fs::path(RayerFileSystem::_currentWorkingPath.string() + "/assets/icons/directory_icon.png"));

		_hdrPath = fs::path(RayerFileSystem::_currentWorkingPath.string() + "/assets/hdri/autumn_field_environment_map.hdr");
		spheremap = Spheremap::Create(_hdrPath);
			
	}

	void SkyLightComponent::OnUpdate() {



	}

	void SkyLightComponent::OnRender() {

		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed |
			ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

		

		if (ImGui::TreeNodeEx("Skylight", treeNodeFlags)) {
			
			
			ImGui::Text("Path:");
			std::string filePath = _hdrPath.string();
			char buf[1024];
			strncpy(buf, filePath.c_str(), sizeof(buf));
			buf[sizeof(buf) - 1] = 0; // Ensure null-termination

			ImGui::InputText("", buf, IM_ARRAYSIZE(buf), ImGuiInputTextFlags_ReadOnly);
			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			if (ImGui::ImageButton(ImTextureID(folderIcon->GetRendererID()), ImVec2(20, 20), ImVec2(0, 1), ImVec2(1, 0))) {

				fs::path _filePath = platformUtils->OpenFileDialog(".hdr");

				if (!_filePath.empty() && _filePath.extension() == ".hdr") {

					_hdrPath = std::move(_filePath);
					spheremap->Invalidate(_hdrPath);


				}

				else {

					LogManager::Get()->AddLog({ LogLevel::LOG_LEVEL_ERROR , std::string("Failed to add texture! Possible reasons: Path does not exist or file format is incorrect or not supported.") });
				}

			}
			ImGui::PopStyleColor();

			ImGui::TreePop();
		}

		ImGui::Separator();

	}

	void SkyLightComponent::Activate() {

		spheremap->Bind();

	}

}
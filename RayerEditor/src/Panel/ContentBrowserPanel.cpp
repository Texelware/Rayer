#include <imgui.h>

#include <Panel/ContentBrowserPanel.h>
#include <Rayer/Filesystem/FileSystem.h>

#include <Rayer.h>

namespace Rayer {

	bool ImageTextButton(ImTextureID tex_id, const ImVec2& size, const char* label, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), int frame_padding = -1, const ImVec4& bg_col = ImVec4(0, 0, 0, 0), const ImVec4& tint_col = ImVec4(1, 1, 1, 1))
	{
		ImGui::BeginGroup(); // Start a group to encapsulate the button

		// Get the starting position of the group
		ImVec2 startPos = ImGui::GetCursorScreenPos();

		// Draw the image
		ImGui::Image(tex_id, size, uv0, uv1, tint_col, bg_col);
		ImGui::SameLine(); // Keep the text on the same line
		ImGui::Text("%s", label); // Draw the text
		ImGui::EndGroup(); // End the group

		// Calculate the size of the group
		ImVec2 itemSize = ImGui::GetItemRectSize();
		ImVec2 itemPos = startPos;

		// Create an invisible button over the entire group
		ImGui::SetCursorScreenPos(itemPos); // Set the cursor to the position of the item
		bool isClicked = ImGui::InvisibleButton("##imagetextbutton", itemSize);

		// Draw the hover effect
		if (ImGui::IsItemHovered())
		{
			ImGui::GetWindowDrawList()->AddRect(itemPos, ImVec2(itemPos.x + itemSize.x, itemPos.y + itemSize.y), IM_COL32(255, 255, 255, 255)); // White border on hover
		}

		return isClicked;
	}



	bool ContentBrowserPanel::showContentBrowser = true;

	ContentBrowserPanel::ContentBrowserPanel() {
		
			m_PlatformUtils = PlatformUtils::Create();

			assetDir = RayerFileSystem::_currentWorkingPath.string() + "/contents/assets";

			m_CurrentDirectory = assetDir.c_str();
			m_BaseDirectory = assetDir.c_str();

			directoryTexture = Texture2D::Create(std::string("assets/icons/directory_icon.png"));
			fileTexture = Texture2D::Create(std::string("assets/icons/file_icon.png"));
			backTexture = Texture2D::Create(std::string("assets/icons/back_icon.png"));
			importTexture = Texture2D::Create(std::string("assets/icons/import_icon.png"));
			modelTexture = Texture2D::Create(std::string("assets/icons/model_icon.png"));
	}

	void ContentBrowserPanel::OnImGuiRender() {

		if (showContentBrowser) {

			ImGui::Begin("Content Browser", &showContentBrowser);

			if (m_CurrentDirectory != m_BaseDirectory) {

				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

				if (ImGui::ImageButton(ImTextureID(backTexture->GetRendererID()), ImVec2(30, 30), ImVec2(0, 1), ImVec2(1, 0))) {

					m_CurrentDirectory = m_CurrentDirectory.parent_path();

				}

				if (ImGui::IsWindowHovered()) {

					if (Input::IsKeyPressed(Key::Backspace)) {

						m_CurrentDirectory = m_CurrentDirectory.parent_path();

					}

				}

				ImGui::PopStyleColor();
				

			}


			ImGui::SameLine();

			if (ImageTextButton(ImTextureID(importTexture->GetRendererID()), ImVec2(30, 30), "Import")) {

				fs::path _path = m_PlatformUtils->OpenFileDialog("*");

				if (!_path.empty()) {
					RayerFileSystem::CopyFileToDirectory(_path, m_CurrentDirectory);
				}

			}

			ImGui::Separator();

			// Get the available window width
			float panelWidth = ImGui::GetContentRegionAvail().x;
			float itemWidth = 120.0f; // Width of each item including padding
			int columns = std::max(1, static_cast<int>(panelWidth / itemWidth));
		
			ImGui::Columns(columns, 0, false);

			
			for (auto& p : fs::directory_iterator(m_CurrentDirectory)) {

				

				auto& path = p.path();
				std::string filenameString = path.filename().string();

				ImGui::PushID(filenameString.c_str());
				if (p.is_directory()) {

					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

					ImGui::ImageButton(ImTextureID(directoryTexture->GetRendererID()), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));

					
					ImGui::PopStyleColor();

					
				}
				else if (p.is_regular_file()) {

					if (path.extension() == ".obj" || path.extension() == ".fbx") {

						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
						ImGui::ImageButton(ImTextureID(modelTexture->GetRendererID()), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
					}

					else {
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
						ImGui::ImageButton(ImTextureID(fileTexture->GetRendererID()), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
					}
					
					ImGui::PopStyleColor();
				}

				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
				{
					if (p.is_directory()) {

						m_CurrentDirectory /= path.filename();

					}

				}

				if (ImGui::BeginDragDropSource())
				{
					std::filesystem::path _Path(path);
					const wchar_t* itemPath = _Path.c_str();
					ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));

					if (path.extension() == ".obj" || path.extension() == ".fbx") {
						ImGui::Image(ImTextureID(modelTexture->GetRendererID()), ImVec2(60, 60), ImVec2(0, 1), ImVec2(1, 0));
					}

					else {

						ImGui::Image(ImTextureID(fileTexture->GetRendererID()), ImVec2(60, 60), ImVec2(0, 1), ImVec2(1, 0));

					}
					

					ImGui::EndDragDropSource();
				}

				ImGui::TextWrapped(filenameString.c_str());
				
				ImGui::NextColumn();

				ImGui::PopID();
			}


			ImGui::Columns(1);

			ImGui::End();

		}


		

	}

	void ContentBrowserPanel::OnFileDropped(int count, const char** paths) {

		for (int i = 0; i < count; ++i) {

			fs::path _path = paths[i];
			RayerFileSystem::CopyFileToDirectory(_path, m_CurrentDirectory);
		}

	}
}
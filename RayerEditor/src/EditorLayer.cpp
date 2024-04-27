#include <imgui.h>
#include <initializer_list>
#include <EditorLayer.h>


namespace Rayer {



	EditorLayer::EditorLayer(): Layer("UI_LAYER") {

		//Initializing or allocation memory for unique panel pointers
		scene_hierarchy_panel = CreateScope<SceneHierarchyPanel>();
		content_browser_panel = CreateScope<ContentBrowserPanel>();
		console_panel = CreateScope<ConsolePanel>();

		//Creating platform specific utility
		platformUtility = PlatformUtils::Create();


	}


	void EditorLayer::OnAttach() {

		MESH_BENCH_ENGINE = CreateScope<MeshBench>();

		//Initializing those dummy objects
		vBuffer = VertexBuffer::Create(vertices, 12 * sizeof(float));
		iBuffer = IndexBuffer::Create(indices, 6);

		vArray = VertexArray::Create();

		bLayout = new BufferLayout({ {ShaderDataType::Float , "aPosition", false}
			});

		fb = Framebuffer::Create({ 1280 , 720 });

		vBuffer->SetBufferLayout(*bLayout);

		vArray->SetVertexBuffer(vBuffer);
		vArray->SetIndexBuffer(iBuffer);

	}

	void EditorLayer::OnUpdate() {

		fb->Resize(viewportWidth, viewportHeight);
		fb->Bind();
		
		MESH_BENCH_ENGINE->SetClearColor({0.0f, 1.0f, 0.5f, 1.0f});
		MESH_BENCH_ENGINE->Clear();
		
		MESH_BENCH_ENGINE->DrawIndexed(vArray, 6);

		fb->Unbind();
	


	}


	void EditorLayer::OnImGuiRender() {

		// Note: Switch this to true to enable dockspace
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;


		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}


		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;


		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("New")) {
			}

			if (ImGui::BeginMenu("Import")) {
				if (ImGui::MenuItem("FBX")) {
					// Action for selecting FBX import

				}

				if (ImGui::MenuItem("OBJ")) {
					// Action for selecting OBJ import

				}

				if (ImGui::MenuItem("GLTF")) {
					// Action for selecting GLTF import

				}

				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Open", "Ctrl+O")) {

				
				m_ProjectOpen = true;

			}

			if (ImGui::MenuItem("Save", "Ctrl+S")) {

			}

			if (ImGui::MenuItem("Save as..")) {
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Settings")) {
			if (ImGui::MenuItem("Preferences", "Ctrl+P")) {



			}
			if (ImGui::MenuItem("Project Settings", "Ctrl+Q")) {




			}

			ImGui::EndMenu();
		}


		if (ImGui::BeginMenu("Help")) {
			if (ImGui::MenuItem("About Rayer")) {
				// Set a flag to open the popup

			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();

		scene_hierarchy_panel->OnImGuiRender();
		content_browser_panel->OnImGuiRender();
		console_panel->OnImGuiRender();

		//Viewport window
		ImGui::Begin("Viewport");

			ImVec2 viewportSize = ImGui::GetContentRegionAvail();

			viewportWidth = (uint32_t)viewportSize.x;
			viewportHeight = (uint32_t)viewportSize.y;

			ImGui::Image((void*)fb->GetColorAttachmentID(), viewportSize);


		ImGui::End();


		/////////////////////POPUPS///////////////////
		if (m_ProjectOpen)
		{
			ImGui::OpenPopup("Save?");
			if (ImGui::BeginPopupModal("Save?", &m_ProjectOpen, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text("Do you want to save your changes?\n\n");
				ImGui::Separator();

				if (ImGui::Button("OK", ImVec2(120, 0))) {
					
					//TODO : Implement saving changes logic
					/**********/
					/**********/
					/**********/
					/**********/
					/**********/

					m_ProjectOpen = false;
					FILEPATH filepath = platformUtility->OpenFileDialog(".rayer");

					if (!filepath.empty())
					{
						OpenProject(filepath);
					}

					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (ImGui::Button("Cancel", ImVec2(120, 0))) {
					ImGui::CloseCurrentPopup();
					m_ProjectOpen = false;
					FILEPATH filepath = platformUtility->OpenFileDialog(".rayer");

					if (!filepath.empty())
					{
						OpenProject(filepath);
					}
				}

				ImGui::EndPopup();
			}
		}

		
		ImGui::End();
	

	}


	//Project opening method
	void EditorLayer::OpenProject(FILEPATH& filepath , Ref<Scene> scene) {

		if (filepath.extension() != ".rayer") {
			std::cout << "Not a valid rayer project" << std::endl;
			return;
		}

		//TODO: Load project from file
		
	}





}
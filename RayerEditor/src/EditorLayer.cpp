#include <imgui.h>
#include <ImGuizmo.h>

#include <initializer_list>
#include <EditorLayer.h>

#include <Rayer/Log/Logger.h>

#include <glm/gtc/type_ptr.hpp>
#include <Rayer/Component/TransformComponent.h>

#include <Rayer/Filesystem/FileSystem.h>

namespace Rayer {

	
	EditorLayer::EditorLayer() : Layer("UI_LAYER") {

		rayerLogo = Texture2D::Create(std::string("assets/logo/Rayer-logo.png"));

		MESH_BENCH_ENGINE = CreateScope<MeshBench>();
		RAYER_X_ENGINE = CreateScope<RayerX>();

		//Add your model imports here 
		model_import_configs = {

			{"FBX" , ".fbx"},
			{"OBJ" , ".obj"}

		};

		//Initializing or allocation memory for unique panel pointers
		scene_hierarchy_panel = CreateScope<SceneHierarchyPanel>();
		content_browser_panel = CreateScope<ContentBrowserPanel>();
		console_panel = CreateScope<ConsolePanel>();

		//Creating platform specific utility
		platformUtility = PlatformUtils::Create();


		
	}



	void EditorLayer::OnAttach() {

		FramebufferSpecification fbSpec;
		fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
		fbSpec.Width = 1280;
		fbSpec.Height = 720;

		fb = Framebuffer::Create(fbSpec);


		vArray = VertexArray::Create();

		bLayout = new BufferLayout({

			{ShaderDataType::Float3 , "aPosition", false},
			{ShaderDataType::Float3 , "aNormal", false},
			{ShaderDataType::Float2 , "UV", false}

			});



	}

	void EditorLayer::OnUpdate() {

		MESH_BENCH_ENGINE->Init();
		//MESH_BENCH_ENGINE->SetViewport(viewportPositionX, viewportPositionY, viewportWidth, viewportHeight);
		MESH_BENCH_ENGINE->SetViewport(0, 0, viewportWidth, viewportHeight);

		editor_camera.SetViewportSize((float)viewportWidth, (float)viewportHeight);

		fb->Resize(viewportWidth, viewportHeight);
		fb->Bind();

		

		MESH_BENCH_ENGINE->SetClearColor({ 0.3f, 0.3f, 0.3f, 1.0f });
		MESH_BENCH_ENGINE->Clear();
		

		MESH_BENCH_ENGINE->SetShaderFloat3("modelColor", { 1.0, 1.0, 1.0 });
		fb->ClearAttachment(1, -1);

		if (m_ViewportState == ViewportState::Hovered || m_ViewportState == ViewportState::Focused) {

			editor_camera.OnUpdate();

			

		}

		
		

		// Get the iterators for the models in the scene
		auto entityBegin = Application::Get().GetScene()->getEntityIteratorBeginC();
		auto entityEnd = Application::Get().GetScene()->getEntityIteratorEndC();

		if (entityBegin != entityEnd) {
			// Iterate over the models in the scene and draw each one
			for (auto entityIt = entityBegin; entityIt != entityEnd; ++entityIt) {

				
				const Ref<Entity> entity = *entityIt;

				switch (entity->GetEntityType()) {

					case EntityType::Model:

						std::dynamic_pointer_cast<Model>(entity)->GetVertexBuffer()->SetBufferLayout(*bLayout);


						vArray->SetVertexBuffer(std::dynamic_pointer_cast<Model>(entity)->GetVertexBuffer());
						vArray->SetIndexBuffer(std::dynamic_pointer_cast<Model>(entity)->GetIndexBuffer());

				}

				


				
				switch (m_ViewType) {

					case ViewType::Solid:

						MESH_BENCH_ENGINE->SetShaderInt("u_EID", entity->GetEntityID());

						switch (entity->GetEntityType()) {

							case EntityType::Model:


								MESH_BENCH_ENGINE->SetShaderMat4("model", std::dynamic_pointer_cast<Model>(entity)->GetModelMatrix());
								MESH_BENCH_ENGINE->SetShaderMat4("view", editor_camera.GetViewMatrix());
								MESH_BENCH_ENGINE->SetShaderMat4("projection", editor_camera.GetProjectionMatrix());

								MESH_BENCH_ENGINE->DrawIndexed(vArray, std::dynamic_pointer_cast<Model>(entity)->GetTotalIndexCount());

								break;
						}

						
						break;


					case ViewType::Wireframe:

						MESH_BENCH_ENGINE->SetShaderInt("u_EID", entity->GetEntityID());

						switch (entity->GetEntityType()) {

						case EntityType::Model:
							//Rndering green wireframe to the selected object in wireframe view
							if (entity->GetEntityID() == Scene::selectedEntityID) {

								MESH_BENCH_ENGINE->SetShaderFloat3("modelColor", { 0.0, 1.0, 0.0 });

							}

							MESH_BENCH_ENGINE->SetShaderMat4("model", std::dynamic_pointer_cast<Model>(entity)->GetModelMatrix());
							MESH_BENCH_ENGINE->SetShaderMat4("view", editor_camera.GetViewMatrix());
							MESH_BENCH_ENGINE->SetShaderMat4("projection", editor_camera.GetProjectionMatrix());

							MESH_BENCH_ENGINE->DrawWireframe(vArray, std::dynamic_pointer_cast<Model>(entity)->GetTotalIndexCount());

							MESH_BENCH_ENGINE->SetShaderFloat3("modelColor", { 1.0, 1.0, 1.0 });

							break;
						}

						break;

					case ViewType::Rendered:

						RAYER_X_ENGINE->SetShaderInt("u_EID", entity->GetEntityID());

						switch (entity->GetEntityType()) {

						case EntityType::Model: {

							MaterialComponent* materialComponent = dynamic_cast<MaterialComponent*>(entity->GetComponent(ComponentType::MaterialComponent));

							if (materialComponent) {

								Ref<Material>& material = materialComponent->GetMaterial();

								if (materialComponent->GetMaterial()->GetMaterialType() == MaterialType::BASIC) {

									
									Ref<BASIC_Material> basicMaterial = std::dynamic_pointer_cast<BASIC_Material>(material);

									RAYER_X_ENGINE->SetShaderBool("u_IsBasic", true);
									RAYER_X_ENGINE->SetShaderBool("u_IsPBR", false);

									RAYER_X_ENGINE->SetShaderFloat4("modelColor", basicMaterial->GetColor());
								}

								else if(materialComponent->GetMaterial()->GetMaterialType() == MaterialType::PBR) {

									Ref<PBR_Material> pbrMaterial = std::dynamic_pointer_cast<PBR_Material>(material);

									

									if(pbrMaterial->GetTextureAvailabilityStatus().has_albedo && pbrMaterial->GetTextureAvailabilityStatus().has_normal){

										pbrMaterial->GetMaterialMaps()->albedo->Bind(1);
										pbrMaterial->GetMaterialMaps()->normal->Bind(2);

										RAYER_X_ENGINE->SetShaderBool("u_IsBasic", false);
										RAYER_X_ENGINE->SetShaderBool("u_IsPBR", true);

										RAYER_X_ENGINE->SetShaderInt("u_DiffuseMap", RAYER_ALBEDO_SLOT);
										RAYER_X_ENGINE->SetShaderInt("u_NormalMap", RAYER_NORMAL_SLOT);

									}

									if (pbrMaterial->GetTextureAvailabilityStatus().has_albedo) {

										pbrMaterial->GetMaterialMaps()->albedo->Bind(1);


										RAYER_X_ENGINE->SetShaderBool("u_IsBasic", false);
										RAYER_X_ENGINE->SetShaderBool("u_IsPBR", true);

										RAYER_X_ENGINE->SetShaderInt("u_DiffuseMap", RAYER_ALBEDO_SLOT);

									}


									if (pbrMaterial->GetTextureAvailabilityStatus().has_normal) {

										pbrMaterial->GetMaterialMaps()->normal->Bind(RAYER_NORMAL_SLOT);


										RAYER_X_ENGINE->SetShaderBool("u_IsBasic", false);
										RAYER_X_ENGINE->SetShaderBool("u_IsPBR", true);

										RAYER_X_ENGINE->SetShaderInt("u_NormalMap", RAYER_NORMAL_SLOT);

									}

									if (!pbrMaterial->GetTextureAvailabilityStatus().has_albedo && !pbrMaterial->GetTextureAvailabilityStatus().has_normal) {

										RAYER_X_ENGINE->SetShaderBool("u_IsBasic", true);
										RAYER_X_ENGINE->SetShaderBool("u_IsPBR", false);
										RAYER_X_ENGINE->SetShaderFloat4("modelColor", { 1.0f , 1.0f , 1.0f, 1.0f });

									}

									RAYER_X_ENGINE->SetShaderUnsignedInt("texFlags", pbrMaterial->GetAvailableTextureMaps());

								}

							}

							else {

								RAYER_X_ENGINE->SetShaderBool("u_IsBasic", true);
								RAYER_X_ENGINE->SetShaderBool("u_IsPBR", false);
								RAYER_X_ENGINE->SetShaderFloat4("modelColor", { 1.0f , 1.0f , 1.0f, 1.0f });


							}

							RAYER_X_ENGINE->SetShaderMat4("model", std::dynamic_pointer_cast<Model>(entity)->GetModelMatrix());
							RAYER_X_ENGINE->SetShaderMat4("view", editor_camera.GetViewMatrix());
							RAYER_X_ENGINE->SetShaderMat4("projection", editor_camera.GetProjectionMatrix());

							RAYER_X_ENGINE->DrawIndexed(vArray, std::dynamic_pointer_cast<Model>(entity)->GetTotalIndexCount());
							break;
						}
						}

						break;

					
				}
			}
		}

		auto [mx, my] = ImGui::GetMousePos();
		mx -= m_ViewportBounds[0].x;
		my -= m_ViewportBounds[0].y;
		glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
		my = viewportSize.y - my;
		int mouseX = (int)mx;
		int mouseY = (int)my;

		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
		{
			int pixelData = fb->ReadPixel(1, mouseX, mouseY);

			if (Input::IsMouseButtonPressed(Mouse::Button0)) {
				Scene::selectedEntityID = pixelData == -1 ? -1 : pixelData;
			}
		}

		if (m_ViewportState == ViewportState::Hovered) {

			//Delete entities when window is hovered and delete key is pressed 
			if (Input::IsKeyPressed(Key::Delete)) {

				if (Scene::selectedEntityID != -1) {

					Application::Get().GetScene()->RemoveEntity(Scene::selectedEntityID);

				}

			}

		}

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


				for (auto element : model_import_configs) {

					if (ImGui::MenuItem(element.format.c_str())) {
						// Action for selecting model import
						FILEPATH filepath = platformUtility->OpenFileDialog(element.extension);

						AddNewModel(filepath, element.extension);

					}

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
				m_AboutOpen = true;
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();

		scene_hierarchy_panel->OnImGuiRender();
		content_browser_panel->OnImGuiRender();
		console_panel->OnImGuiRender();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		//Viewport window
		ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		ImVec2 viewportPos = ImGui::GetWindowPos();

		viewportWidth = (uint32_t)viewportSize.x;
		viewportHeight = (uint32_t)viewportSize.y;

		viewportPositionX = (uint32_t)viewportPos.x;
		viewportPositionY = (uint32_t)viewportPos.y;


		//------------------Viewport State Checking--------------------


		if (ImGui::IsWindowHovered()) {

			m_ViewportState = ViewportState::Hovered;

		}

		
		else if (ImGui::IsAnyItemFocused()) {

			m_ViewportState = ViewportState::Focused;
		}

		

		else {

			m_ViewportState = ViewportState::None;

		}

		



		ImGui::Image(ImTextureID((void*)fb->GetColorAttachmentRendererID()), viewportSize , ImVec2(0, 1), ImVec2(1, 0));


		

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
			{
				const wchar_t* path = (const wchar_t*)payload->Data;

				// Find the last occurrence of a dot in the path
				const wchar_t* extension = wcsrchr(path, L'.');

				if (extension != nullptr)
				{
					// Compare the extension with desired extensions
					if (wcscmp(extension, L".obj") == 0)
					{
						// Handle .obj files
						fs::path _filePath = path;
						AddNewModel(_filePath , ".obj");

						#ifdef RAYER_DEBUG

						std::cout << "Dragged a .obj file" << std::endl;

						#endif

					}
					
				}

				else
				{
					
				}
			}
			ImGui::EndDragDropTarget();
		}

		

		// Get the iterators for the models in the scene
		auto entityBegin = Application::Get().GetScene()->getEntityIteratorBeginC();
		auto entityEnd = Application::Get().GetScene()->getEntityIteratorEndC();

		if (entityBegin != entityEnd) {
			// Iterate over the models in the scene and draw each one
			for (auto entityIt = entityBegin; entityIt != entityEnd; ++entityIt) {

				const Ref<Entity> entity = *entityIt;

				if (Scene::selectedEntityID == entity->GetEntityID()) {

					ImGuizmo::BeginFrame();

					ImGuizmo::SetDrawlist();

					ImGuizmo::SetOrthographic(false);
					ImGuizmo::SetRect(m_ViewportBounds[0].x, m_ViewportBounds[0].y, m_ViewportBounds[1].x - m_ViewportBounds[0].x, m_ViewportBounds[1].y - m_ViewportBounds[0].y);


					TransformComponent* transformation = dynamic_cast<TransformComponent*>(entity->GetComponent(ComponentType::TransformComponent));

					if (transformation == nullptr) {

						std::cout << "No Transform component found!" << std::endl;

					}

					
					//Handling transformation
					switch (m_CurrentTransformationType)
					{
						
					

						case TransformType::None:
							ImGuizmo::Enable(false);
							break;
						case TransformType::TRANSLATE:

							switch (entity->GetEntityType()) {

							case EntityType::Model:

								ImGuizmo::Enable(true);
								ImGuizmo::Manipulate(glm::value_ptr(editor_camera.GetViewMatrix()),
									glm::value_ptr(editor_camera.GetProjectionMatrix()), ImGuizmo::TRANSLATE, ImGuizmo::WORLD, 
									glm::value_ptr(transformation->GetTransformationMatrix()));
								break;
							}
							
							break;

						case TransformType::ROTATE:

							switch (entity->GetEntityType()) {

							case EntityType::Model:
								ImGuizmo::Enable(true);
								ImGuizmo::Manipulate(glm::value_ptr(editor_camera.GetViewMatrix()),
									glm::value_ptr(editor_camera.GetProjectionMatrix()), ImGuizmo::ROTATE, ImGuizmo::WORLD, 
									glm::value_ptr(transformation->GetTransformationMatrix()));
								break;
							}

							break;

						case TransformType::SCALE:

							switch (entity->GetEntityType()) {

							case EntityType::Model:
								ImGuizmo::Enable(true);
								ImGuizmo::Manipulate(glm::value_ptr(editor_camera.GetViewMatrix()),
									glm::value_ptr(editor_camera.GetProjectionMatrix()), ImGuizmo::SCALE, ImGuizmo::WORLD, 
									glm::value_ptr(transformation->GetTransformationMatrix()));
								break;
							}

							break;
					}
					

					

				}



			}
		}


		ImGui::End();

		ImGui::PopStyleVar();

		/////////////////////POPUPS///////////////////
		if (m_ProjectOpen)
		{
			ImGui::OpenPopup("Save");
			if (ImGui::BeginPopupModal("Save", &m_ProjectOpen, ImGuiWindowFlags_AlwaysAutoResize))
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



		if (m_AboutOpen)
		{
			ImGui::OpenPopup("About");
			if (ImGui::BeginPopupModal("About", &m_AboutOpen, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Image(ImTextureID(rayerLogo->GetRendererID()), ImVec2(100, 100) , ImVec2(0, 1), ImVec2(1, 0));
				ImGui::Separator();

				ImGui::Text("Version : Development Version.");
				ImGui::Separator();
				ImGui::Text("Icons by : Icons8.");

				ImGui::EndPopup();
			}
		}


		ImGui::End();


	}


	//Project opening method
	void EditorLayer::OpenProject(FILEPATH& filepath, Ref<Scene> scene) {

		if (filepath.extension() != ".rayer") {

			#ifdef RAYER_DEBUG
				std::cout << "Not a valid rayer project" << std::endl;
			#endif

			LogManager::Get()->AddLog({ LogLevel::LOG_LEVEL_ERROR , std::string("Not a valid rayer project")});
			return;
		}

		//TODO: Load project from file

	}


	void EditorLayer::AddNewModel(FILEPATH& filepath, const std::string& extension) {

		if (filepath.extension() != extension) {

			#ifdef RAYER_DEBUG
				std::cout << "Not a valid " << extension << " file" << std::endl;
			#endif
			std::string msg = "Not a valid " + extension + " file";

			LogManager::Get()->AddLog({ LogLevel::LOG_LEVEL_ERROR , msg });

			return;
		}

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

		Ref<Entity> model = CreateRef<Model>(entityName, Scene::nextEntityID ,  EntityType::Model, filepath);
		Scene::nextEntityID++;
		
		if (std::dynamic_pointer_cast<Model>(model)->IsReadSuccessful()) {
			// Adding a new model into the current scene
			Application::Get().GetScene()->AddEntity(model);
		}

		else {


		}


	}


	///////////////////////////////////////////////
	//////////////////Events//////////////////////
	/////////////////////////////////////////////

	void EditorLayer::OnEvent(Event& e) {

		if (m_ViewportState == ViewportState::Hovered || m_ViewportState == ViewportState::Focused) {
			editor_camera.OnEvent(e);
		}

		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<KeyPressedEvent>(RAYER_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<FileDroppedEvent>(RAYER_BIND_EVENT_FN(EditorLayer::OnFileDropped));
	

	}


	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e) {

		#ifdef RAYER_DEBUG
				std::cout << e.ToString() << std::endl;
		#endif

		if (e.IsRepeat())
			return false;


		// Check if Ctrl+N is pressed
		if ((Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl)) && Input::IsKeyPressed(Key::O)) {

			m_ProjectOpen = true;
			return true;
		}
		

		// Check if Alt+W is pressed
		if ((Input::IsKeyPressed(Key::LeftAlt) || Input::IsKeyPressed(Key::RightAlt)) && Input::IsKeyPressed(Key::W)) {



			m_ViewType = ViewType::Wireframe;

			return true;
		}


		// Check if Alt+R is pressed
		if ((Input::IsKeyPressed(Key::LeftAlt) || Input::IsKeyPressed(Key::RightAlt)) && Input::IsKeyPressed(Key::R)) {



			m_ViewType = ViewType::Rendered;
			

			return true;
		}


		// Check if Alt+S is pressed
		if ((Input::IsKeyPressed(Key::LeftAlt) || Input::IsKeyPressed(Key::RightAlt)) && Input::IsKeyPressed(Key::S)) {


			m_ViewType = ViewType::Solid;
		

			return true;
		}
		
		
		//Changing trasfromation based on currently selected transformation type
		if (m_ViewportState == ViewportState::Hovered) {

			switch (e.GetKeyCode()) {

				case Key::W :
				//Switching to translate if [W] key is pressed
				{
					if (m_CurrentTransformationType == TransformType::TRANSLATE) {
						m_CurrentTransformationType = TransformType::None;
					}

					else {
						m_CurrentTransformationType = TransformType::TRANSLATE;
					}

					break;

				}

				case Key::E :
				//Switching to rotate if [E] key is pressed
				{
					if (m_CurrentTransformationType == TransformType::ROTATE) {
						m_CurrentTransformationType = TransformType::None;
					}

					else {
						m_CurrentTransformationType = TransformType::ROTATE;
					}

					break;

				}

				case Key::R:
					//Switching to scale if [R] key is pressed
				{
					if (m_CurrentTransformationType == TransformType::SCALE) {
						m_CurrentTransformationType = TransformType::None;
					}

					else {
						m_CurrentTransformationType = TransformType::SCALE;
					}

					break;
				}

			}
			
			return true;

		}


		return false;
	}

	bool EditorLayer::OnFileDropped(FileDroppedEvent& e) {

		#ifdef RAYER_DEBUG
				std::cout << e.ToString() << std::endl;
		#endif // RAYER_DEBUG


		content_browser_panel->OnFileDropped(e.GetFileCount(), e.GetPaths());

		return true;

	}

	

}
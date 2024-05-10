#include <imgui.h>
#include <ImGuizmo.h>
#include <initializer_list>
#include <EditorLayer.h>

#include <glm/gtc/type_ptr.hpp>

namespace Rayer {

	

	EditorLayer::EditorLayer() : Layer("UI_LAYER") {

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

		


		vArray = VertexArray::Create();

		bLayout = new BufferLayout({

			{ShaderDataType::Float3 , "aPosition", false},
			{ShaderDataType::Float3 , "aNormal", false},
			{ShaderDataType::Float2 , "UV", false}

			});



		fb = Framebuffer::Create({ 1280 , 720 });


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

		if (m_ViewportState == ViewportState::Hovered || m_ViewportState == ViewportState::Focused) {

			editor_camera.OnUpdate();

		}



		// Get the iterators for the models in the scene
		auto modelBegin = Application::Get().GetScene()->getModelIteratorBeginC();
		auto modelEnd = Application::Get().GetScene()->getModelIteratorEndC();

		if (modelBegin != modelEnd) {
			// Iterate over the models in the scene and draw each one
			for (auto modelIt = modelBegin; modelIt != modelEnd; ++modelIt) {

				const Ref<Model> model = *modelIt;

				model->GetVertexBuffer()->SetBufferLayout(*bLayout);

				vArray->SetVertexBuffer(model->GetVertexBuffer());
				vArray->SetIndexBuffer(model->GetIndexBuffer());


				


				switch (m_ViewType) {

					case ViewType::Solid:
						MESH_BENCH_ENGINE->SetShaderMat4("model", model->GetModelMatrix());
						MESH_BENCH_ENGINE->SetShaderMat4("view", editor_camera.GetViewMatrix());
						MESH_BENCH_ENGINE->SetShaderMat4("projection", editor_camera.GetProjectionMatrix());

						

						MESH_BENCH_ENGINE->DrawIndexed(vArray, model->GetTotalIndexCount());

						break;
					case ViewType::Wireframe:

						if (model->GetModelName() == Scene::selectedObjectName) {

							MESH_BENCH_ENGINE->SetShaderFloat3("modelColor", { 0.0, 1.0, 0.0 });

						}

						MESH_BENCH_ENGINE->SetShaderMat4("model", model->GetModelMatrix());
						MESH_BENCH_ENGINE->SetShaderMat4("view", editor_camera.GetViewMatrix());
						MESH_BENCH_ENGINE->SetShaderMat4("projection", editor_camera.GetProjectionMatrix());

						MESH_BENCH_ENGINE->DrawWireframe(vArray, model->GetTotalIndexCount());

						MESH_BENCH_ENGINE->SetShaderFloat3("modelColor", { 1.0, 1.0, 1.0 });

						break;

					case ViewType::Rendered:

						RAYER_X_ENGINE->SetShaderMat4("model", model->GetModelMatrix());
						RAYER_X_ENGINE->SetShaderMat4("view", editor_camera.GetViewMatrix());
						RAYER_X_ENGINE->SetShaderMat4("projection", editor_camera.GetProjectionMatrix());

						RAYER_X_ENGINE->DrawIndexed(vArray, model->GetTotalIndexCount());

						break;

					
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

			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();

		scene_hierarchy_panel->OnImGuiRender();
		content_browser_panel->OnImGuiRender();
		console_panel->OnImGuiRender();

		//Viewport window
		ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		// Get the main viewport


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

		



		ImGui::Image((void*)fb->GetColorAttachmentID(), viewportSize);

		// Get the iterators for the models in the scene
		auto modelBegin = Application::Get().GetScene()->getModelIteratorBeginC();
		auto modelEnd = Application::Get().GetScene()->getModelIteratorEndC();

		if (modelBegin != modelEnd) {
			// Iterate over the models in the scene and draw each one
			for (auto modelIt = modelBegin; modelIt != modelEnd; ++modelIt) {

				const Ref<Model> model = *modelIt;

				if (Scene::selectedObjectName == model->GetModelName()) {

					ImGuizmo::BeginFrame();

					ImGuizmo::SetDrawlist();

					ImGuizmo::SetOrthographic(false);
					ImGuizmo::SetRect(viewportPositionX, viewportPositionY, viewportWidth, viewportHeight);

					//Handling transformation
					switch (m_CurrentTransformationType)
					{
						
						case TransformType::None:
							ImGuizmo::Enable(false);
							break;
						case TransformType::TRANSLATE:
							ImGuizmo::Enable(true);
							ImGuizmo::Manipulate(glm::value_ptr(editor_camera.GetViewMatrix()),
								glm::value_ptr(editor_camera.GetProjectionMatrix()), ImGuizmo::TRANSLATE, ImGuizmo::WORLD, glm::value_ptr(model->GetModelMatrix()));
							break;

						case TransformType::ROTATE:
							ImGuizmo::Enable(true);
							ImGuizmo::Manipulate(glm::value_ptr(editor_camera.GetViewMatrix()),
								glm::value_ptr(editor_camera.GetProjectionMatrix()), ImGuizmo::ROTATE, ImGuizmo::WORLD, glm::value_ptr(model->GetModelMatrix()));
							break;

						case TransformType::SCALE:
							ImGuizmo::Enable(true);
							ImGuizmo::Manipulate(glm::value_ptr(editor_camera.GetViewMatrix()),
								glm::value_ptr(editor_camera.GetProjectionMatrix()), ImGuizmo::SCALE , ImGuizmo::WORLD, glm::value_ptr(model->GetModelMatrix()));
							break;

					}
					

					

				}



			}
		}


		ImGui::End();


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


		ImGui::End();


	}


	//Project opening method
	void EditorLayer::OpenProject(FILEPATH& filepath, Ref<Scene> scene) {

		if (filepath.extension() != ".rayer") {
			std::cout << "Not a valid rayer project" << std::endl;
			
			return;
		}

		//TODO: Load project from file

	}


	void EditorLayer::AddNewModel(FILEPATH& filepath, const std::string& extension) {

		if (filepath.extension() != extension) {
			std::cout << "Not a valid " << extension << " file" << std::endl;
		
			return;
		}

		std::string modelName = filepath.stem().string();
		auto beginIt = Application::Get().GetScene()->getModelIteratorBeginC();
		auto endIt = Application::Get().GetScene()->getModelIteratorEndC();

		// Check if the model name already exists
		int count = 1;
		std::string originalName = modelName;
		while (std::find_if(beginIt, endIt, [&](const Ref<Model>& model) { return model->GetModelName() == modelName; }) != endIt) {
			modelName = originalName + "(" + std::to_string(count) + ")";
			count++;
		}

		Ref<Model> model = CreateRef<Model>(modelName, filepath);

		if (model->IsReadSuccessful()) {
			// Adding a new model into the current scene
			Application::Get().GetScene()->AddModel(model);
		}
	}


	///////////////////////////////////////////////
	//////////////////Events//////////////////////
	/////////////////////////////////////////////

	void EditorLayer::OnEvent(Event& e) {

		if (m_ViewportState == ViewportState::Hovered) {
			editor_camera.OnEvent(e);
		}

		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<KeyPressedEvent>(RAYER_BIND_EVENT_FN(EditorLayer::OnKeyPressed));

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



}
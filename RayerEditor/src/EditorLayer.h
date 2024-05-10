#pragma once
#include <Panel/SceneHierarchyPanel.h>
#include <Panel/ContentBrowserPanel.h>
#include <Panel/ConsolePanel.h>
#include <Rayer.h>

//Camera header
#include <Rayer/Camera/EditorCamera.h>


namespace Rayer {

	

	struct ModelImportConfig {

		std::string format;
		std::string extension;

	};

	enum class ViewType {

		None = 0,
		Solid,
		Wireframe,
		Rendered

	};

	enum class TransformType {
		
		None = 0,
		TRANSLATE,
		ROTATE,
		SCALE

	};


	enum class ViewportState {

		None = 0,
		Hovered,
		Focused

	};
	
	
	class EditorLayer : public Layer{

		public:

			using FILEPATH = std::filesystem::path;

			EditorLayer();

			virtual void OnEvent(Event& e) override;
			virtual void OnAttach() override;

			virtual void OnUpdate() override;

			virtual void OnImGuiRender() override;

			void OpenProject(FILEPATH& filepath , Ref<Scene> scene = Application::Get().GetScene() );

			void AddNewModel(FILEPATH& filepath , const std::string& extension);


			////////////////////////////////////////////////////////////////
			//
			//        Callbacks
			//
			///////////////////////////////////////////////////////////////

			bool OnKeyPressed(KeyPressedEvent& e);


		private:


			//Unique pointer to the content_browser_panel
			Scope<ContentBrowserPanel> content_browser_panel;

			//Unique pointer to the scene_hierarchy_panel
			Scope<SceneHierarchyPanel> scene_hierarchy_panel;

			//Unique pointer to the console
			Scope<ConsolePanel> console_panel;

			//Viewport size
			uint32_t viewportWidth { 1280 };
			uint32_t viewportHeight { 720 };

			//Viewport position
			uint32_t viewportPositionX	{ 0 };
			uint32_t viewportPositionY	{ 0 };

			
			
			//VertexArray
			Ref<VertexArray> vArray;

			//Dummy object
			BufferLayout* bLayout;


			//Refrences to the render engines
			Scope<MeshBench> MESH_BENCH_ENGINE;
			Scope<RayerX> RAYER_X_ENGINE;

			Ref<Framebuffer> fb;

			Scope<PlatformUtils> platformUtility;

			std::vector<ModelImportConfig> model_import_configs;

			//Project opening boolean
			bool m_ProjectOpen = false;

			//Viewport camera
			EditorCamera editor_camera;

			//Viewport state
			ViewportState m_ViewportState { ViewportState::None };
			ViewType m_ViewType{ ViewType::Solid };

			//Current transformation type
			TransformType m_CurrentTransformationType{ TransformType::None };


	};

}



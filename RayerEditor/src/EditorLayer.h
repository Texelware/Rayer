#pragma once
#include <Panel/SceneHierarchyPanel.h>
#include <Panel/ContentBrowserPanel.h>
#include <Panel/ConsolePanel.h>
#include <Rayer.h>


namespace Rayer {


	struct ModelImportConfig {

		std::string format;
		std::string extension;

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

			uint32_t viewportWidth{ 1280 };
			uint32_t viewportHeight{ 720 };

			
			
			//VertexArray
			Ref<VertexArray> vArray;

			//Dummy object
			BufferLayout* bLayout;


			//Refrences to the render engines
			Scope<MeshBench> MESH_BENCH_ENGINE;

			Ref<Framebuffer> fb;

			Scope<PlatformUtils> platformUtility;

			std::vector<ModelImportConfig> model_import_configs;

			//Project opening boolean
			bool m_ProjectOpen = false;





	};

}



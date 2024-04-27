#pragma once
#include <Panel/SceneHierarchyPanel.h>
#include <Panel/ContentBrowserPanel.h>
#include <Panel/ConsolePanel.h>
#include <Rayer.h>


namespace Rayer {

	
	class EditorLayer : public Layer{

		public:

			using FILEPATH = std::filesystem::path;

			EditorLayer();

			virtual void OnAttach() override;

			virtual void OnUpdate() override;

			virtual void OnImGuiRender() override;

			void OpenProject(FILEPATH& filepath , Ref<Scene> scene = Application::Get().GetScene() );

			

		private:

			

			//Unique pointer to the content_browser_panel
			Scope<ContentBrowserPanel> content_browser_panel;

			//Unique pointer to the scene_hierarchy_panel
			Scope<SceneHierarchyPanel> scene_hierarchy_panel;

			//Unique pointer to the console
			Scope<ConsolePanel> console_panel;

			uint32_t viewportWidth = 1280;
			uint32_t viewportHeight = 720;


			//Dummy vertex and index data => Only for testing
			float vertices[12] = {
				// Positions
				-0.5f,  0.5f, 0.0f, // Top Left
				 0.5f,  0.5f, 0.0f, // Top Right
				 0.5f, -0.5f, 0.0f, // Bottom Right
				-0.5f, -0.5f, 0.0f  // Bottom Left
			};
			unsigned int indices[6] = {
				0, 1, 2, // First Triangle
				2, 3, 0  // Second Triangle
			};

			//Dummy objects => Only for testing
			//VertexBuffer
			Ref<VertexBuffer> vBuffer;
			//Index Buffer
			Ref<IndexBuffer> iBuffer;
			//VertexArray
			Ref<VertexArray> vArray;

			//Dummy object
			BufferLayout* bLayout;


			//Refrences to the render engines
			Scope<MeshBench> MESH_BENCH_ENGINE;

			Ref<Framebuffer> fb;

			Scope<PlatformUtils> platformUtility;


			//Project opening boolean
			bool m_ProjectOpen = false;

	};

}



#pragma once
#include <Panel/SceneHierarchyPanel.h>
#include <Panel/ContentBrowserPanel.h>
#include <Rayer.h>

namespace Rayer {

	class EditorLayer : public Layer{

		public:

			EditorLayer() : Layer("EDITOR_LAYER") {

				//Initializing or allocation memory for unique panel pointers
				scene_hierarchy_panel = std::make_unique<SceneHierarchyPanel>();
				content_browser_panel = std::make_unique<ContentBrowserPanel>();
			
			}

			virtual void OnImGuiRender() override;

		private:

			//Unique pointer to the content_browser_panel
			std::unique_ptr<ContentBrowserPanel> content_browser_panel;

			//Unique pointer to the scene_hierarchy_panel
			std::unique_ptr<SceneHierarchyPanel> scene_hierarchy_panel;
			
	};

}



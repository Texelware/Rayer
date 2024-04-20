#pragma once
#include <Panel/SceneHierarchyPanel.h>
#include <Panel/ContentBrowserPanel.h>
#include <Panel/ConsolePanel.h>
#include <Rayer.h>

namespace Rayer {

	class EditorLayer : public Layer{

		public:

			EditorLayer();

		

			virtual void OnImGuiRender() override;

		private:

			//Unique pointer to the content_browser_panel
			std::unique_ptr<ContentBrowserPanel> content_browser_panel;

			//Unique pointer to the scene_hierarchy_panel
			std::unique_ptr<SceneHierarchyPanel> scene_hierarchy_panel;

			//Unique pointer to the console
			std::unique_ptr<ConsolePanel> console_panel;
			
	};

}



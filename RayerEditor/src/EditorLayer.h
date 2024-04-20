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
			Scope<ContentBrowserPanel> content_browser_panel;

			//Unique pointer to the scene_hierarchy_panel
			Scope<SceneHierarchyPanel> scene_hierarchy_panel;

			//Unique pointer to the console
			Scope<ConsolePanel> console_panel;
			
	};

}



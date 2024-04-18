#include <imgui.h>

#include <Panel/ContentBrowserPanel.h>

namespace Rayer {

	bool ContentBrowserPanel::showContentBrowser = true;

	void ContentBrowserPanel::OnImGuiRender() {

		if (showContentBrowser) {

			ImGui::Begin("Content Browser", &showContentBrowser);

			ImGui::End();

		}

	}

}
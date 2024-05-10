#include <imgui.h>
#include <Panel/ConsolePanel.h>




namespace Rayer {

    //Declare the static
    bool ConsolePanel::showConsolePanel = true;

    void ConsolePanel::OnImGuiRender() {
        if (showConsolePanel) {
            ImGui::Begin("Console", &showConsolePanel);

         
               
            
            ImGui::End();
        }
    }

} // namespace Rayer

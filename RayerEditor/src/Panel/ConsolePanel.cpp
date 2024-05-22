#include <imgui.h>
#include <Panel/ConsolePanel.h>
#include <Rayer/Log/Logger.h>

namespace Rayer {

    // Declare the static
    bool ConsolePanel::showConsolePanel = true;

    void ConsolePanel::OnImGuiRender() {
        if (showConsolePanel) {
            ImGui::Begin("Console", &showConsolePanel, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

            if (ImGui::Button("Clear")) {

                LogManager::Get()->ClearLogs();

            }

            ImGui::Separator();

            auto beginIt = LogManager::Get()->GetLogsBegin();
            auto endIt = LogManager::Get()->GetLogsEnd();

            // Adding some padding
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 4));
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 4));

            if (beginIt != endIt) {
                // Enable scrollbar if needed
                ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

                for (auto it = beginIt; it != endIt; ++it) {
                    Log log = *it;

                    switch (log.level) {
                    case LogLevel::LOG_LEVEL_ERROR:
                        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "[ERROR] %s", log.message.c_str());
                        break;
                    case LogLevel::LOG_LEVEL_WARN:
                        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "[WARN] %s", log.message.c_str());
                        break;
                    case LogLevel::LOG_LEVEL_INFO:
                        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "[INFO] %s", log.message.c_str());
                        break;
                    }
                }

                ImGui::EndChild();
            }
            

            // Restore style settings
            ImGui::PopStyleVar(2);

            ImGui::End();
        }
    }

} // namespace Rayer

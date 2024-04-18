#pragma once



//-----------Event-----------
#include <Rayer/Event/Event.h>

//----------Layer------------
#include <Rayer/Core/Layer.h>




namespace Rayer {

    enum class ThemeType {

		Dark = 0,
		Light = 1

    };

    class ImGuiLayer : public Layer {

    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnEvent(Event& e) override;

        void SetThemeColors(ThemeType type);

		void Begin();
		void End();

    private:
 

        float m_Time = 0.0f;
    };

} // namespace Rayer

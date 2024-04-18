
#include <rpch.h>

#include <Rayer/Core/LayerStack.h>


namespace Rayer {

    LayerStack::LayerStack() {
       
    }

    LayerStack::~LayerStack() {
        for (Layer* layer : m_Layers) {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer) {

        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;

    }

    void LayerStack::PushOverlay(Layer* overlay) {
        m_Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer) {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if (it != m_Layers.end()) {
            m_Layers.erase(it);
        }
        else {
            std::cerr << "Warning: Layer not found in LayerStack::PopLayer()\n";
        }
    }

    void LayerStack::PopOverlay(Layer* overlay) {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
        if (it != m_Layers.end()) {
            m_Layers.erase(it);
        }
        else {
            std::cerr << "Warning: Overlay not found in LayerStack::PopOverlay()\n";
        }
    }



} // namespace Rayer

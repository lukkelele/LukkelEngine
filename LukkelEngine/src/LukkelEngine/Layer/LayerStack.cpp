#include <LukkelEngine/Layer/LayerStack.h>

/*
  - LayerStack
	Layers are pushed to the front of the layer queue and 
	overlays are pushed to the back.
	This is because overlays should ALWAYS be rendered last.
*/

namespace LukkelEngine {

	/*
		Terminate layers upon deconstructor call 
		This implementation makes it so that all layers get destroyed
		whenever the application is to terminate.
	*/
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers) {
			layer->onDetach();
			delete layer;
		}
	}

	/* Push layer to the front of the queue */
	void LayerStack::pushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	/* Push overlay to the back of the queue */
	void LayerStack::pushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	/* Pop layer */
	void LayerStack::popLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_Layers.begin() + m_LayerInsertIndex) {
			layer->onDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	/* Pop overlay */
	void LayerStack::popOverlay(Layer* overlay)
	{   /* Start iterator on .begin() and index count to make sure overlays are targeted */
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			overlay->onDetach();
			m_Layers.erase(it);
		}
	}
}
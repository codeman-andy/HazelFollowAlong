#include "LayerStack.h"

namespace Hazel {

	Hazel::LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (it != m_Layers.end())
		{
			m_Layers.erase(it); // This will erase the pointer to the Layer's address, not the Layer itself, so that it can be reinserted later if we want to
			m_LayerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);

		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			// The m_LayerInsert points to the next location to insert a Layer in,
			// while the overlays are always placed at the back which is automatically
			// serviced by the <vector> library, so they do not require a pointer and
			// thus we do not have to increment/decrement any sort of iterator as well
		}
	}

}
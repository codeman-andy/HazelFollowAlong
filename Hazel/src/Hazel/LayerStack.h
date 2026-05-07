#pragma once

#include <vector>

#include "Core.h"
#include "Layer.h"


namespace Hazel {

	// The LayerStack is essentially a wrapper over the 'std::vector<Layer*> m_Layers' member. Vectors allow for reverse-iterators
	class HAZEL_API LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		// These items are so m_Layers can be used in a based-range for-loop in other parts of our program
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;
	};

}
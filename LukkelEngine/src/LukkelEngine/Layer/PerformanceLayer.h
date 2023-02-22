#include "LukkelEngine/Core/Layer.h"



namespace LukkelEngine {

	class PerformanceLayer : public Layer
	{
	public:
		PerformanceLayer();
		~PerformanceLayer() = default;

		void onUpdate(float ts);
		void onImGuiRender();

		void FPS();
	};

}
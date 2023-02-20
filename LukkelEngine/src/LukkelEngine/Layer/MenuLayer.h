#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Core/Layer.h"

namespace LukkelEngine {

	class MenuLayer : public Layer
	{
	public:
		MenuLayer();
		~MenuLayer() = default;

		void begin();
		void end();
		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onUpdate(float ts) override;

		virtual void onImGuiRender() override;
		void onEvent(LukkelEngine::Event& e) override;

	};

}
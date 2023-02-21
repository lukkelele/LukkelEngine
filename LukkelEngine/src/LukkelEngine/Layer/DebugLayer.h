#pragma once
#include "LukkelEngine/Core/Layer.h"
#include "LukkelEngine/Test/Test.h"
#include "LukkelEngine/Test/TestClearColor.h"
#include "LukkelEngine/Test/TestTexture2D.h"
#include "LukkelEngine/Test/TestDrawTriangle.h"
#include "LukkelEngine/Test/TestDrawTriangle2.h"
#include "LukkelEngine/Test/TestDrawCube.h"
#include "LukkelEngine/Test/TestShader.h"

#include "imgui/imgui.h"

namespace LukkelEngine {

	class DebugLayer : public Layer
	{
	public:
		DebugLayer();
		~DebugLayer() = default;

		void onUpdate(float ts);
		void renderTestMenu();
		void registerTests();

	private:
		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu;
	};
}

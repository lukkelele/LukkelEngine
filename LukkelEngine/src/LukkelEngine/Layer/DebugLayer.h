#pragma once
#include "LukkelEngine/Core/Layer.h"
#include "LukkelEngine/Debug/Test/Test.h"
#include "LukkelEngine/Debug/Test/TestClearColor.h"
#include "LukkelEngine/Debug/Test/TestTexture2D.h"
#include "LukkelEngine/Debug/Test/TestDrawTriangle.h"
#include "LukkelEngine/Debug/Test/TestDrawTriangle2.h"
#include "LukkelEngine/Debug/Test/TestDrawCube.h"
#include "LukkelEngine/Debug/Test/TestShader.h"

#include "imgui/imgui.h"

namespace LukkelEngine {

	class DebugLayer : public Layer
	{
	public:
		DebugLayer();
		~DebugLayer() = default;

		void onUpdate(float ts);
		void onImGuiRender();

		void renderTestMenu();
		void registerTests();

	private:
		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu;
	};
}

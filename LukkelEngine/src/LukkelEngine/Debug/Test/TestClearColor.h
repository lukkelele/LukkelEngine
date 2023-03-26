#pragma once
#include "LukkelEngine/Debug/Test/Test.h"

namespace LukkelEngine {

	namespace test {

		class TestClearColor : public Test
		{
		public:
			TestClearColor();
			~TestClearColor();

			void OnUpdate(float deltaTime) override;
			void onRender() override;
			void OnImGuiRender() override;

		private:
			float m_clearColor[4];
		};

	}
}

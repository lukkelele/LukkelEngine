#ifndef _TEST_CLEARCOLOR_H
#define _TEST_CLEARCOLOR_H

#include <Test.h>

namespace test {

	class ClearColor : public Test
	{
	public:
		ClearColor();
		~ClearColor();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;

	private:
		float m_clearColor[4];
	};

}

#endif /* _TEST_CLEARCOLOR_H */
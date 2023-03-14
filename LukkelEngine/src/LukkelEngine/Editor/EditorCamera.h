#pragma once
#include "LukkelEngine/Renderer/Camera.h"
#include "LukkelEngine/Input/Keyboard.h"
#include "LukkelEngine/Input/Mouse.h"

namespace LukkelEngine {

	class EditorCamera	: public Camera
	{
	public:
		EditorCamera(float FOV, float nearPlane, float farPlane);
		~EditorCamera() = default;

		void onUpdate(float ts) override;
		void onImGuiRender() override;

	};

}

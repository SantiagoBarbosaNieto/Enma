#pragma once

#include "Enma/Core/Core.h"
#include "Enma/Core/KeyCodes.h"
#include "Enma/Core/MouseCodes.h"
#include "Enma/Core/GamepadCodes.h"


namespace Enma
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(KeyCode keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static bool IsGamepadButtonPressed(GamepadButton button) { return s_Instance->IsGamepadButtonPressedImpl(button); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		inline static std::pair<float,float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
		virtual bool IsGamepadButtonPressedImpl(GamepadButton button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
	private:
		static Scope<Input> s_Instance;
	};
}
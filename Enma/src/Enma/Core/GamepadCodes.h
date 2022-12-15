#pragma once
namespace Enma 
{
	typedef enum class GamepadButton : uint16_t
	{
		A = 0,
		B = 1,
		X = 2,
		Y = 3,

		//L1, R1
		LeftBumper = 4,
		RightBumper = 5,

		Back = 6,
		Start = 7,
		Guide = 8,

		//L3, R3
		LeftThumb = 9,
		RightThumb = 10,

		DPadUp = 11,
		DPadRight = 12,
		DPadDown = 13,
		DPadLeft = 14,
		DPadLast = DPadLeft,

		//PS
		Cross = A,
		Circle = B,
		Square = X,
		Triangle = Y
	};

	inline std::ostream& operator<<(std::ostream& os, GamepadButton keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}

	typedef enum class GamepadAxis : uint16_t
	{
		LeftX = 0,
		LeftY = 1,
		RightX = 2,
		RightY = 3,
		LeftTrigger = 4,
		RightTrigger = 5,
		Last = RightTrigger
	};

	inline std::ostream& operator<<(std::ostream& os, GamepadAxis keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

//Buttons
#define EM_GAMEPAD_BUTTON_A					::Enma::GamepadButton::A
#define EM_GAMEPAD_BUTTON_B					::Enma::GamepadButton::B
#define EM_GAMEPAD_BUTTON_X					::Enma::GamepadButton::X
#define EM_GAMEPAD_BUTTON_Y					::Enma::GamepadButton::Y
#define EM_GAMEPAD_BUTTON_LEFT_BUMPER		::Enma::GamepadButton::LeftBumper
#define EM_GAMEPAD_BUTTON_RIGHT_BUMPER		::Enma::GamepadButton::RightBumper
#define EM_GAMEPAD_BUTTON_BACK				::Enma::GamepadButton::Back
#define EM_GAMEPAD_BUTTON_START				::Enma::GamepadButton::Start
#define EM_GAMEPAD_BUTTON_GUIDE				::Enma::GamepadButton::Guide
#define EM_GAMEPAD_BUTTON_LEFT_THUMB		::Enma::GamepadButton::LeftThumb
#define EM_GAMEPAD_BUTTON_RIGHT_THUMB		::Enma::GamepadButton::RightThumb
#define EM_GAMEPAD_BUTTON_DPAD_UP			::Enma::GamepadButton::DPadUp
#define EM_GAMEPAD_BUTTON_DPAD_RIGHT		::Enma::GamepadButton::DPadRight
#define EM_GAMEPAD_BUTTON_DPAD_DOWN			::Enma::GamepadButton::DPadDown
#define EM_GAMEPAD_BUTTON_DPAD_LEFT			::Enma::GamepadButton::DPadLeft
#define EM_GAMEPAD_BUTTON_DPAD_LAST			::Enma::GamepadButton::DPadLast
#define EM_GAMEPAD_BUTTON_CROSS				::Enma::GamepadButton::Cross
#define EM_GAMEPAD_BUTTON_CICLE				::Enma::GamepadButton::Circle
#define EM_GAMEPAD_BUTTON_SQUARE			::Enma::GamepadButton::Square
#define EM_GAMEPAD_BUTTON_TRIANGLE			::Enma::GamepadButton::Triangle

//Axis
#define EM_GAMEPAD_AXIS_LEFT_X				::Enma::GamepadAxis::LeftX
#define EM_GAMEPAD_AXIS_LEFT_Y				::Enma::GamepadAxis::LeftY
#define EM_GAMEPAD_AXIS_RIGHT_X				::Enma::GamepadAxis::RightX
#define EM_GAMEPAD_AXIS_RIGHT_Y				::Enma::GamepadAxis::RightY
#define EM_GAMEPAD_AXIS_TRIGGER_LEFT		::Enma::GamepadAxis::LeftTrigger
#define EM_GAMEPAD_AXIS_TRIGGER_RIGHT		::Enma::GamepadAxis::RightTrigger
#define EM_GAMEPAD_AXIS_TRIGGER_LAST		::Enma::GamepadAxis::Last
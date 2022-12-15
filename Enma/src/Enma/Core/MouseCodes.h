#pragma once

namespace Enma
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}


#define EM_MOUSE_BUTTON_0      ::Enma::Mouse::Button0
#define EM_MOUSE_BUTTON_1      ::Enma::Mouse::Button1
#define EM_MOUSE_BUTTON_2      ::Enma::Mouse::Button2
#define EM_MOUSE_BUTTON_3      ::Enma::Mouse::Button3
#define EM_MOUSE_BUTTON_4      ::Enma::Mouse::Button4
#define EM_MOUSE_BUTTON_5      ::Enma::Mouse::Button5
#define EM_MOUSE_BUTTON_6      ::Enma::Mouse::Button6
#define EM_MOUSE_BUTTON_7      ::Enma::Mouse::Button7
#define EM_MOUSE_BUTTON_LAST   ::Enma::Mouse::ButtonLast
#define EM_MOUSE_BUTTON_LEFT   ::Enma::Mouse::ButtonLeft
#define EM_MOUSE_BUTTON_RIGHT  ::Enma::Mouse::ButtonRight
#define EM_MOUSE_BUTTON_MIDDLE ::Enma::Mouse::ButtonMiddle
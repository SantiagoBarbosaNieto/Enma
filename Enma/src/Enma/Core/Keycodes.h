#pragma once

namespace Enma
{

	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define EM_KEY_SPACE           ::Enma::Key::Space
#define EM_KEY_APOSTROPHE      ::Enma::Key::Apostrophe    /* ' */
#define EM_KEY_COMMA           ::Enma::Key::Comma         /* , */
#define EM_KEY_MINUS           ::Enma::Key::Minus         /* - */
#define EM_KEY_PERIOD          ::Enma::Key::Period        /* . */
#define EM_KEY_SLASH           ::Enma::Key::Slash         /* / */
#define EM_KEY_0               ::Enma::Key::D0
#define EM_KEY_1               ::Enma::Key::D1
#define EM_KEY_2               ::Enma::Key::D2
#define EM_KEY_3               ::Enma::Key::D3
#define EM_KEY_4               ::Enma::Key::D4
#define EM_KEY_5               ::Enma::Key::D5
#define EM_KEY_6               ::Enma::Key::D6
#define EM_KEY_7               ::Enma::Key::D7
#define EM_KEY_8               ::Enma::Key::D8
#define EM_KEY_9               ::Enma::Key::D9
#define EM_KEY_SEMICOLON       ::Enma::Key::Semicolon     /* ; */
#define EM_KEY_EQUAL           ::Enma::Key::Equal         /* = */
#define EM_KEY_A               ::Enma::Key::A
#define EM_KEY_B               ::Enma::Key::B
#define EM_KEY_C               ::Enma::Key::C
#define EM_KEY_D               ::Enma::Key::D
#define EM_KEY_E               ::Enma::Key::E
#define EM_KEY_F               ::Enma::Key::F
#define EM_KEY_G               ::Enma::Key::G
#define EM_KEY_H               ::Enma::Key::H
#define EM_KEY_I               ::Enma::Key::I
#define EM_KEY_J               ::Enma::Key::J
#define EM_KEY_K               ::Enma::Key::K
#define EM_KEY_L               ::Enma::Key::L
#define EM_KEY_M               ::Enma::Key::M
#define EM_KEY_N               ::Enma::Key::N
#define EM_KEY_O               ::Enma::Key::O
#define EM_KEY_P               ::Enma::Key::P
#define EM_KEY_Q               ::Enma::Key::Q
#define EM_KEY_R               ::Enma::Key::R
#define EM_KEY_S               ::Enma::Key::S
#define EM_KEY_T               ::Enma::Key::T
#define EM_KEY_U               ::Enma::Key::U
#define EM_KEY_V               ::Enma::Key::V
#define EM_KEY_W               ::Enma::Key::W
#define EM_KEY_X               ::Enma::Key::X
#define EM_KEY_Y               ::Enma::Key::Y
#define EM_KEY_Z               ::Enma::Key::Z
#define EM_KEY_LEFT_BRACKET    ::Enma::Key::LeftBracket   /* [ */
#define EM_KEY_BACKSLASH       ::Enma::Key::Backslash     /* \ */
#define EM_KEY_RIGHT_BRACKET   ::Enma::Key::RightBracket  /* ] */
#define EM_KEY_GRAVE_ACCENT    ::Enma::Key::GraveAccent   /* ` */
#define EM_KEY_WORLD_1         ::Enma::Key::World1        /* non-US #1 */
#define EM_KEY_WORLD_2         ::Enma::Key::World2        /* non-US #2 */

/* Function keys */
#define EM_KEY_ESCAPE          ::Enma::Key::Escape
#define EM_KEY_ENTER           ::Enma::Key::Enter
#define EM_KEY_TAB             ::Enma::Key::Tab
#define EM_KEY_BACKSPACE       ::Enma::Key::Backspace
#define EM_KEY_INSERT          ::Enma::Key::Insert
#define EM_KEY_DELETE          ::Enma::Key::Delete
#define EM_KEY_RIGHT           ::Enma::Key::Right
#define EM_KEY_LEFT            ::Enma::Key::Left
#define EM_KEY_DOWN            ::Enma::Key::Down
#define EM_KEY_UP              ::Enma::Key::Up
#define EM_KEY_PAGE_UP         ::Enma::Key::PageUp
#define EM_KEY_PAGE_DOWN       ::Enma::Key::PageDown
#define EM_KEY_HOME            ::Enma::Key::Home
#define EM_KEY_END             ::Enma::Key::End
#define EM_KEY_CAPS_LOCK       ::Enma::Key::CapsLock
#define EM_KEY_SCROLL_LOCK     ::Enma::Key::ScrollLock
#define EM_KEY_NUM_LOCK        ::Enma::Key::NumLock
#define EM_KEY_PRINT_SCREEN    ::Enma::Key::PrintScreen
#define EM_KEY_PAUSE           ::Enma::Key::Pause
#define EM_KEY_F1              ::Enma::Key::F1
#define EM_KEY_F2              ::Enma::Key::F2
#define EM_KEY_F3              ::Enma::Key::F3
#define EM_KEY_F4              ::Enma::Key::F4
#define EM_KEY_F5              ::Enma::Key::F5
#define EM_KEY_F6              ::Enma::Key::F6
#define EM_KEY_F7              ::Enma::Key::F7
#define EM_KEY_F8              ::Enma::Key::F8
#define EM_KEY_F9              ::Enma::Key::F9
#define EM_KEY_F10             ::Enma::Key::F10
#define EM_KEY_F11             ::Enma::Key::F11
#define EM_KEY_F12             ::Enma::Key::F12
#define EM_KEY_F13             ::Enma::Key::F13
#define EM_KEY_F14             ::Enma::Key::F14
#define EM_KEY_F15             ::Enma::Key::F15
#define EM_KEY_F16             ::Enma::Key::F16
#define EM_KEY_F17             ::Enma::Key::F17
#define EM_KEY_F18             ::Enma::Key::F18
#define EM_KEY_F19             ::Enma::Key::F19
#define EM_KEY_F20             ::Enma::Key::F20
#define EM_KEY_F21             ::Enma::Key::F21
#define EM_KEY_F22             ::Enma::Key::F22
#define EM_KEY_F23             ::Enma::Key::F23
#define EM_KEY_F24             ::Enma::Key::F24
#define EM_KEY_F25             ::Enma::Key::F25

/* Keypad */
#define EM_KEY_KP_0            ::Enma::Key::KP0
#define EM_KEY_KP_1            ::Enma::Key::KP1
#define EM_KEY_KP_2            ::Enma::Key::KP2
#define EM_KEY_KP_3            ::Enma::Key::KP3
#define EM_KEY_KP_4            ::Enma::Key::KP4
#define EM_KEY_KP_5            ::Enma::Key::KP5
#define EM_KEY_KP_6            ::Enma::Key::KP6
#define EM_KEY_KP_7            ::Enma::Key::KP7
#define EM_KEY_KP_8            ::Enma::Key::KP8
#define EM_KEY_KP_9            ::Enma::Key::KP9
#define EM_KEY_KP_DECIMAL      ::Enma::Key::KPDecimal
#define EM_KEY_KP_DIVIDE       ::Enma::Key::KPDivide
#define EM_KEY_KP_MULTIPLY     ::Enma::Key::KPMultiply
#define EM_KEY_KP_SUBTRACT     ::Enma::Key::KPSubtract
#define EM_KEY_KP_ADD          ::Enma::Key::KPAdd
#define EM_KEY_KP_ENTER        ::Enma::Key::KPEnter
#define EM_KEY_KP_EQUAL        ::Enma::Key::KPEqual

#define EM_KEY_LEFT_SHIFT      ::Enma::Key::LeftShift
#define EM_KEY_LEFT_CONTROL    ::Enma::Key::LeftControl
#define EM_KEY_LEFT_ALT        ::Enma::Key::LeftAlt
#define EM_KEY_LEFT_SUPER      ::Enma::Key::LeftSuper
#define EM_KEY_RIGHT_SHIFT     ::Enma::Key::RightShift
#define EM_KEY_RIGHT_CONTROL   ::Enma::Key::RightControl
#define EM_KEY_RIGHT_ALT       ::Enma::Key::RightAlt
#define EM_KEY_RIGHT_SUPER     ::Enma::Key::RightSuper
#define EM_KEY_MENU            ::Enma::Key::Menu
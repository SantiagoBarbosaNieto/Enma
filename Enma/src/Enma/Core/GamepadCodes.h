#pragma once
namespace Enma 
{
	using KeyCodes = unsigned int;
	namespace Gamepad
	{
		namespace Button
		{
			enum : KeyCodes
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

		}

		namespace Axis
		{
			enum : KeyCodes
			{
				LeftX = 0,
				LeftY = 1,
				RightX = 2,
				RightY = 3,
				LeftTrigger = 4,
				RightTrigger = 5,
				Last = RightTrigger
			};
		}
	}
	
}
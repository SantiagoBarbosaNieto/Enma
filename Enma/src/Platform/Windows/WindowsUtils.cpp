#include "empch.h"
#include "WindowsUtils.h"

#include <GLFW/glfw3.h>

namespace Enma
{
	Time* Time::s_Instance = new WindowsTime();

	float WindowsTime::GetSecondsImpl()
	{
		return s_Time;
	}

	float WindowsTime::GetMillisecondsImpl()
	{
		return s_Time.GetMilliseconds();
	}

	float WindowsTime::DeltaTimeImpl()
	{
		return s_Time - s_LastFrameTime;
	}

	void WindowsTime::UpdateTimeImpl()
	{
		s_LastFrameTime = s_Time;
		s_Time = glfwGetTime();
	}
}
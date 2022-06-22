#include "empch.h"
#include "WindowsUtils.h"

#include <GLFW/glfw3.h>

namespace Enma
{
	Time* Time::s_Instance = new WindowsTime();

	float WindowsTime::GetSecondsImpl()
	{
		return m_Time;
	}

	float WindowsTime::GetMillisecondsImpl()
	{
		return m_Time.GetMilliseconds();
	}

	float WindowsTime::DeltaTimeImpl()
	{
		return m_Time - m_LastFrameTime;
	}

	void WindowsTime::UpdateTimeImpl()
	{
		m_LastFrameTime = m_Time;
		m_Time = glfwGetTime();
	}
}
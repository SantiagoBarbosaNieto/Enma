#pragma once

#include "Enma/Core/Time.h"

namespace Enma
{
	class WindowsTime : public Time
	{
	public:
		virtual float GetSecondsImpl() override;
		virtual float GetMillisecondsImpl() override;
		virtual float DeltaTimeImpl() override;
		virtual void UpdateTimeImpl() override;
	private:
		 Timestep s_Time;
		 Timestep s_LastFrameTime;
	};
}
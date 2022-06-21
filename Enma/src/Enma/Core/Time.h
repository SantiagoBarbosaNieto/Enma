#pragma once
#include "Timestep.h"

namespace Enma
{
	class Time
	{
	public:
		inline static float GetSeconds() { return s_Instance->GetSecondsImpl(); }
		inline static float GetMilliseconds() { return s_Instance->GetMillisecondsImpl(); }
		inline static float DeltaTime() { return s_Instance->DeltaTimeImpl(); }
		inline static void UpdateTime() { return s_Instance->UpdateTimeImpl(); }
	protected:
		
		virtual float GetSecondsImpl() = 0;
		virtual float GetMillisecondsImpl() = 0;
		virtual float DeltaTimeImpl() = 0;
		virtual void UpdateTimeImpl() = 0;

	private:
		static Time* s_Instance;
	};
}
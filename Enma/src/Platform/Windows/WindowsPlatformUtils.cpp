#include "empch.h"
#include "Enma/Utils/PlatformUtils.h"
#include <GLFW/glfw3.h>

namespace Enma
{
	float Platform::GetTime()
	{
		return glfwGetTime();
	}
}
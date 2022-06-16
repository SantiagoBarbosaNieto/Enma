#pragma once

#include "Enma/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Enma
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;

	};
}
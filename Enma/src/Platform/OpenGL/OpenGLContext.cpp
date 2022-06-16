#include "empch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Enma
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		EM_ASSERT(windowHandle, "Handle is null")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EM_ASSERT(status, "Failed to initialize Glad!");

		EM_CORE_INFO("OpenGL context using:");
		EM_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		EM_CORE_INFO("  Rederer: {0}", glGetString(GL_RENDERER));
		EM_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
#include "empch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Enma
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		EM_ASSERT(windowHandle, "Handle is null");
	}

	void OpenGLContext::Init()
	{
		EM_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EM_ASSERT(status, "Failed to initialize Glad!");
 
		EM_CORE_INFO("OpenGL context using:");
		EM_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		EM_CORE_INFO("  Rederer: {0}", glGetString(GL_RENDERER));
		EM_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

	#ifdef EM_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		EM_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Enma requires at least OpenGL version 4.5!");
	#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		EM_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}

}
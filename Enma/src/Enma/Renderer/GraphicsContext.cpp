#include "empch.h"
#include "Enma/Renderer/GraphicsContext.h"

#include "Enma/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Enma {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    EM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		EM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
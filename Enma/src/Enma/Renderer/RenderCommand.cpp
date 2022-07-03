#include "empch.h"
#include "Enma/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Enma
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI; 
}
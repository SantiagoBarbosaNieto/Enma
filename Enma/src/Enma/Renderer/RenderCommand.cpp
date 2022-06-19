#include "empch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Enma
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI; 
}
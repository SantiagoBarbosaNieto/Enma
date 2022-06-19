#include "empch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Enma
{

	Enma::VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		EM_CORE_ASSERT(false, "RendererAPI::None is not supported yet!"); return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}

		EM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
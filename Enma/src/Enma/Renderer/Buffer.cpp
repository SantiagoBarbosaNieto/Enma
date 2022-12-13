#include "empch.h"
#include "Enma/Renderer/Buffer.h"

#include "Enma/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Enma
{

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			EM_CORE_ASSERT(false, "RendererAPI::None is not supported yet!"); 
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		EM_CORE_ASSERT(false, "Unknown renderer API: option {0}", (int)Renderer::GetAPI());
		return nullptr;
	}


	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			EM_CORE_ASSERT(false, "RendererAPI::None is not supported yet!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(indices, count);
		}

		EM_CORE_ASSERT(false, "Unknown renderer API: option {0}", (int)Renderer::GetAPI());
		return nullptr;
	}
}
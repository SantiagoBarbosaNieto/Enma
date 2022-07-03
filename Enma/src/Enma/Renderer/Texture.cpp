#include "empch.h"
#include "Enma/Renderer/Texture.h"

#include "Enma/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Enma
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		EM_CORE_ASSERT(false, "RendererAPI::None is not supported yet!"); return nullptr;
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLTexture2D>( path);
		}

		EM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
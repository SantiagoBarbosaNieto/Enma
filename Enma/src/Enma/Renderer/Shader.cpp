#include "empch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace Enma
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: EM_CORE_ASSERT(false, "RendererAPI::None is not yet supported!");
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		EM_CORE_ASSERT(false, "Unknown rendererAPI!");
		return nullptr;
	}
}
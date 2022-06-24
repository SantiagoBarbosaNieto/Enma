#include "empch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace Enma
{

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		EM_CORE_ASSERT(false, "RendererAPI::None is not yet supported!");
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(filepath);
		}

		EM_CORE_ASSERT(false, "Unknown rendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		EM_CORE_ASSERT(false, "RendererAPI::None is not yet supported!");
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
		}

		EM_CORE_ASSERT(false, "Unknown rendererAPI!");
		return nullptr;
	}
}
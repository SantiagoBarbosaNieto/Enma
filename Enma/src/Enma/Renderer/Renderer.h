#pragma once

#include "RenderCommand.h"

namespace Enma
{

	class Renderer
	{
	public:
		static void BeginScene(); //TODO take all scene parameters
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);



		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
	};
}
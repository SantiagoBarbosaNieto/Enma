#include "empch.h"
#include "Enma/Renderer/Renderer.h"
#include "Enma/Renderer/Renderer2D.h"

namespace Enma
{
	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		EM_PROFILE_FUNCTION();
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ProjectionViewMatrix = camera.GetProjectionViewMatrix();
	}

	void Renderer::EndScene()
	{
		Renderer2D::EndScene();
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		EM_PROFILE_FUNCTION();
		shader->SetMat4("u_ProjectionView", s_SceneData->ProjectionViewMatrix);
		shader->SetMat4("u_Transform", transform);



		vertexArray->Bind();
		{
			EM_PROFILE_SCOPE("Draw Indexed");
			RenderCommand::DrawIndexed(vertexArray);
		}
	}


	void Renderer::OnWindowResize(uint32_t width, uint32_t height) 
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
}
#include "empch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"
namespace Enma
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ProjectionViewMatrix = camera.GetProjectionViewMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ProjectionView", s_SceneData->ProjectionViewMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);



		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}


	void Renderer::OnWindowResize(float width, float height) 
	{
		//TODO
	}
}
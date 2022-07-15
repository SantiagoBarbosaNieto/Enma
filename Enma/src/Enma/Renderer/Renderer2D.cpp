#include "empch.h"
#include "Enma/Renderer/Renderer2D.h"

#include "Enma/Renderer/VertexArray.h"
#include "Enma/Renderer/Shader.h"
#include "Enma/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>


namespace Enma
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader; 
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();

		s_Data->QuadVertexArray = Enma::VertexArray::Create();

		float vertices[5*4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f, 
			 0.5f,  0.5f, 0.0f, 
			-0.5f,  0.5f, 0.0f
		};


		// Vertex Buffer
		Ref<VertexBuffer> vertexBuffer;
		vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" }
		};

		vertexBuffer->SetLayout(layout);
		s_Data->QuadVertexArray->AddVertexBuffer(vertexBuffer);

		// Index Buffer
		unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };

		Ref<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		s_Data->QuadVertexArray->SetIndexBuffer(indexBuffer);

		//Shader
		s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColorShader.glsl");

	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetMat4("u_ProjectionView", camera.GetProjectionViewMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * /*  Rotation   */ glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		s_Data->FlatColorShader->SetMat4("u_Transform",transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}
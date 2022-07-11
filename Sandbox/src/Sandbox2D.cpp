#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Enma::Timestep ts)
{

	//Update
	m_CameraController.OnUpdte(ts);

	//Render
	Enma::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.5f });
	Enma::RenderCommand::Clear();


	Enma::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Enma::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.2f, 0.8f, 0.5f, 1.0f });

	Enma::Renderer2D::EndScene();
	//std::dynamic_pointer_cast<Enma::OpenGLShader>(textureShader)->Bind();
	//Enma::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Color picker");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Enma::Event& e)
{
	m_CameraController.OnEvent(e);
}

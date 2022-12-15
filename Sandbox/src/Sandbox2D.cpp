#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	EM_PROFILE_FUNCTION();

	m_ZoroTexture = Enma::Texture2D::Create("assets/textures/zoro.png");
}

void Sandbox2D::OnDetach()
{
	EM_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Enma::Timestep ts)
{
	EM_PROFILE_FUNCTION();
	//Update
	m_CameraController.OnUpdte(ts);

	{
		EM_PROFILE_SCOPE("RenderDraw");
		//Render
		Enma::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		Enma::RenderCommand::Clear();


		Enma::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Enma::Renderer2D::DrawRotatedQuad({ 1.0f, 1.0f}, { 0.5f, 1.0f },glm::radians(60.0f), m_SquareColor);
		Enma::Renderer2D::DrawQuad({ 2.0f, 1.0f }, { 1.2f, 1.2f }, { 0.8f, 0.2f, 0.2f, 1.0f });
		Enma::Renderer2D::DrawQuad({ 0.0f,0.0f, 0.1f}, { 10.0f,10.0f }, m_ZoroTexture, 1.0f,glm::vec4({0.9f, 0.2f, 0.2f, 0.5f}));
	}

	Enma::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	EM_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Enma::Event& e)
{
	m_CameraController.OnEvent(e);
}

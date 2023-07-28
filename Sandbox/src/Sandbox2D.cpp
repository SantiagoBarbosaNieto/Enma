#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Enma/Utils/PlatformUtils.h"
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
		float time = Enma::Platform::GetTime();
		Enma::Timestep ts = time - m_LastFrameTime;
		m_LastFrameTime = time;

		EM_PROFILE_SCOPE("RenderDraw");
		//Render
		Enma::RenderCommand::SetClearColor({ 0.3f, 0.3f, 0.3f, 1.0f });
		Enma::RenderCommand::Clear();


		Enma::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Enma::Renderer2D::DrawQuad({ 0.0f, 20.0f, -0.2f }, { 300.0f, 40.0f }, m_SkyColor);
		Enma::Renderer2D::DrawQuad({ 0.0f, -10.0f,-0.1f }, { 300.0f, 20.0f }, m_GroundColor);
		//Enma::Renderer2D::DrawQuad({ 10.0f, 0.5f }, { 1.0f,1.0f }, { 1.0f,0.1f,0.1f , 1.0f});

		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				Enma::Renderer2D::DrawRotatedQuad({ i * 1.0f, j * 1.0f, 0.0f }, { 3.0f,3.0f }, glm::radians(m_currentRotation), glm::vec4({i/30.0f, j/30.0f, m_currentRotation/ 255, 1.0f}));
			}
		}
		Enma::Renderer2D::DrawRotatedQuad(m_ZoroPosition, { 3.0f,3.0f }, glm::radians(0.0f), m_ZoroTexture, 1.0f, glm::vec4(m_ZoroTintColor));

		m_currentRotation += m_rotationSpeed * ts.GetSeconds();
		if (m_currentRotation >= 255)
			m_currentRotation = 0.0f;

	}

	Enma::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	EM_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Sky Color", glm::value_ptr(m_SkyColor));
	ImGui::ColorEdit4("Ground Color", glm::value_ptr(m_GroundColor));
	ImGui::SliderFloat3("Zoro Position", glm::value_ptr(m_ZoroPosition), -10.0f, 20.0f);

	ImGui::InputFloat("Rotation Speed", &m_rotationSpeed);

	ImGui::End();
}

void Sandbox2D::OnEvent(Enma::Event& e)
{
	m_CameraController.OnEvent(e);
}

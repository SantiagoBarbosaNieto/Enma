#pragma once
#include <Enma.h>

class Sandbox2D : public Enma::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Enma::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Enma::Event& e) override;
private:
	Enma::OrthographicCameraController m_CameraController;
		
	//Temp
	Enma::Ref<Enma::Shader> m_FlatColorShader;
	Enma::Ref<Enma::Texture2D> m_ZoroTexture;
	Enma::Ref<Enma::VertexArray> m_SquareVertexArray;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;

	glm::vec4 m_SkyColor = { 0.4f, 0.4f, 0.9f, 1.0f };
	glm::vec4 m_GroundColor = { 0.64f, 0.4f, 0.4f, 1.0f };
	glm::vec4 m_ZoroTintColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	glm::vec3 m_ZoroPosition = { 0.0f,1.3f, 0.1f };

	glm::float32_t m_currentRotation = 0.0f;
	glm::float32_t m_LastFrameTime = 0.0f;
	float m_rotationSpeed = 10.0f;



};
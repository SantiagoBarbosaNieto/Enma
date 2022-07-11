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
		
	Enma::Ref<Enma::Shader> m_FlatColorShader;
	Enma::Ref<Enma::Texture2D> m_ZoroTexture;
	Enma::Ref<Enma::VertexArray> m_SquareVertexArray;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

};
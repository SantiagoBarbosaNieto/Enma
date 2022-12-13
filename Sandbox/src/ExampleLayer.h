#pragma once
#include "Enma.h"

class ExampleLayer : public Enma::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Enma::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Enma::Event& e) override;
private:
	Enma::ShaderLibrary m_ShaderLibrary;
	Enma::Ref<Enma::Shader> m_Shader;
	Enma::Ref<Enma::VertexArray> m_VertexArray;

	Enma::Ref<Enma::Shader> m_FlatColorShader;
	Enma::Ref<Enma::VertexArray> m_SquareVA;

	Enma::Ref<Enma::Texture2D> m_Texture, m_ZoroTexture;

	Enma::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
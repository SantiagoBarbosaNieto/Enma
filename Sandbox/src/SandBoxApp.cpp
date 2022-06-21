#include <Enma.h>
#include "imgui/imgui.h"

class ExampleLayer : public Enma::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6, 1.6f, -0.9f, 0.9f), m_CameraPosition({0.0f,0.0f,0.0f})
	{
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		// Vertex Array
		m_VertexArray.reset(Enma::VertexArray::Create());


		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 1.2f, 1.0f
		};


		// Vertex Buffer
		std::shared_ptr<Enma::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Enma::VertexBuffer::Create(vertices, sizeof(vertices)));

		Enma::BufferLayout layout = {
			{ Enma::ShaderDataType::Float3, "a_Position" },
			{ Enma::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);



		// Index Buffer
		unsigned int indices[3] = { 0,1,2 };

		std::shared_ptr<Enma::IndexBuffer> indexBuffer;
		indexBuffer.reset(Enma::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		//Square--------------------------------------------------

		m_SquareVertexArray.reset(Enma::VertexArray::Create());


		float verticesSquare[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Enma::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Enma::VertexBuffer::Create(verticesSquare, sizeof(verticesSquare)));

		squareVertexBuffer->SetLayout({
			{ Enma::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		unsigned int indicesSquare[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<Enma::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Enma::IndexBuffer::Create(indicesSquare, sizeof(indicesSquare) / sizeof(uint32_t)));

		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		// Shader - Triangle
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ProjectionView;

			out vec4 v_Color;
			out vec3 v_Position;
			
			void main()
			{
				v_Position =  a_Position;
				v_Color = a_Color;
				gl_Position = u_ProjectionView * vec4(a_Position,1.0);
				
			}
		)";


		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec4 v_Color;
			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position*0.5 + 0.5, 1.0);
				color = v_Color;
				
			}
		)";

		// Shader - Square
		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ProjectionView;

			out vec3 v_Position;
			
			void main()
			{
				v_Position =  a_Position;
				gl_Position = u_ProjectionView * vec4(a_Position,1.0);
				
			}
		)";


		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
				
			}
		)";

		m_Shader.reset(new Enma::Shader(vertexSrc, fragmentSrc));
		m_BlueShader.reset(new Enma::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));


	}

	void OnUpdate(Enma::Timestep deltaTime) override
	{
		//EM_TRACE("Delta time: {0} s", ts.GetSeconds());

		if (Enma::Input::IsKeyPressed(Enma::Key::Up) || Enma::Input::IsKeyPressed(Enma::Key::W))
			m_CameraPosition.y += m_CameraMoveSpeed * deltaTime;
		else if (Enma::Input::IsKeyPressed(Enma::Key::Down) || Enma::Input::IsKeyPressed(Enma::Key::S))
			m_CameraPosition.y -= m_CameraMoveSpeed * deltaTime;
		
		if (Enma::Input::IsKeyPressed(Enma::Key::Right) || Enma::Input::IsKeyPressed(Enma::Key::D))
			m_CameraPosition.x += m_CameraMoveSpeed * deltaTime;
		else if (Enma::Input::IsKeyPressed(Enma::Key::Left) || Enma::Input::IsKeyPressed(Enma::Key::A))
			m_CameraPosition.x -= m_CameraMoveSpeed * deltaTime;


		if (Enma::Input::IsKeyPressed(Enma::Key::Q))
			m_CameraRotation += m_CameraRotationSpeed * deltaTime;
		else if (Enma::Input::IsKeyPressed(Enma::Key::E))
			m_CameraRotation -= m_CameraRotationSpeed * deltaTime;

		Enma::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.5f });
		Enma::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		Enma::Renderer::BeginScene(m_Camera);

		Enma::Renderer::Submit(m_BlueShader, m_SquareVertexArray);
		Enma::Renderer::Submit(m_Shader, m_VertexArray);

		Enma::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
	}

	void OnEvent(Enma::Event& e) override
	{
		Enma::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Enma::KeyPressedEvent> (EM_BIND_EVENT_FN(ExampleLayer::OnKeyPressed));
	} 

	bool OnKeyPressed(Enma::KeyPressedEvent& e)
	{
		

		return true;
	}
private: 

	std::shared_ptr<Enma::Shader> m_Shader;
	std::shared_ptr<Enma::VertexArray> m_VertexArray;


	std::shared_ptr<Enma::VertexArray> m_SquareVertexArray;
	std::shared_ptr<Enma::Shader> m_BlueShader;

	Enma::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;

	float m_CameraRotation = 0;
	float m_CameraRotationSpeed = 25.0f;
};

class Sandbox : public Enma::Application 
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {

	}
};
Enma::Application* Enma::CreateApplication() {
	return new Sandbox();
}
#include <Enma.h>
#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
		Enma::Ref<Enma::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Enma::VertexBuffer::Create(vertices, sizeof(vertices)));

		Enma::BufferLayout layout = {
			{ Enma::ShaderDataType::Float3, "a_Position" },
			{ Enma::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);



		// Index Buffer
		unsigned int indices[3] = { 0,1,2 };

		Enma::Ref<Enma::IndexBuffer> indexBuffer;
		indexBuffer.reset(Enma::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		//Square--------------------------------------------------

		m_SquareVertexArray.reset(Enma::VertexArray::Create());


		float verticesSquare[5 * 4] = {
			-0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
			 0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
			 0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
			-0.75f,  0.75f, 0.0f, 0.0f, 1.0f
		};

		Enma::Ref<Enma::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Enma::VertexBuffer::Create(verticesSquare, sizeof(verticesSquare)));

		squareVertexBuffer->SetLayout({
			{ Enma::ShaderDataType::Float3, "a_Position" },
			{ Enma::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		unsigned int indicesSquare[6] = { 0, 1, 2, 2, 3, 0 };

		Enma::Ref<Enma::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Enma::IndexBuffer::Create(indicesSquare, sizeof(indicesSquare) / sizeof(uint32_t)));

		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		// Shader - Triangle
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ProjectionView;
			uniform mat4 u_Transform;	 

			out vec4 v_Color;
			out vec3 v_Position;
			
			void main()
			{
				v_Position =  a_Position;
				v_Color = a_Color;
				gl_Position = u_ProjectionView * u_Transform * vec4(a_Position,1.0);
				
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

		// FlatcolorShader
		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ProjectionView;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			
			void main()
			{
				v_Position =  a_Position;
				gl_Position = u_ProjectionView * u_Transform  * vec4(a_Position,1.0);
				
			}
		)";


		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			uniform vec3 u_Color;
			in vec3 v_Position;

			void main()
			{
				color = vec4(u_Color, 1.0f);
				
			}
		)";


		m_Shader = Enma::Shader::Create("VertexPosColor",vertexSrc, fragmentSrc);
		m_FlatColorShader = Enma::Shader::Create("FlatColor",flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		m_ZoroTexture = Enma::Texture2D::Create("assets/textures/zoro.png");


		std::dynamic_pointer_cast<Enma::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Enma::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate() override
	{
		Enma::Timestep deltaTime = Enma::Time::DeltaTime();
		//EM_TRACE("Delta time: {0} s ({1} ms)", deltaTime.GetSeconds(), deltaTime.GetMilliseconds());

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

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		std::dynamic_pointer_cast<Enma::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Enma::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				glm::vec3 pos(i * 0.18f ,j * 0.18f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos ) * scale;
				Enma::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_ZoroTexture->Bind();
		std::dynamic_pointer_cast<Enma::OpenGLShader>(textureShader)->Bind();
		Enma::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//Triangle render
		//Enma::Renderer::Submit(m_Shader, m_VertexArray);

		Enma::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
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
	Enma::ShaderLibrary m_ShaderLibrary; 
	Enma::Ref<Enma::Shader> m_Shader;
	Enma::Ref<Enma::VertexArray> m_VertexArray;


	Enma::Ref<Enma::VertexArray> m_SquareVertexArray;
	Enma::Ref<Enma::Shader> m_FlatColorShader;
	Enma::Ref<Enma::Texture2D> m_ZoroTexture;

	Enma::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 3.0f;

	float m_CameraRotation = 0;
	float m_CameraRotationSpeed = 100.0f;
 
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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
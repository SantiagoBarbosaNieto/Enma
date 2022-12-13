#include "ExampleLayer.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


	ExampleLayer::ExampleLayer()
		:Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{

		// Vertex Array
		m_VertexArray = Enma::VertexArray::Create();


		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 1.2f, 1.0f
		};

		// Vertex Buffer
		Enma::Ref<Enma::VertexBuffer> vertexBuffer;
		vertexBuffer = Enma::VertexBuffer::Create(vertices, sizeof(vertices));

		Enma::BufferLayout layout = {
			{ Enma::ShaderDataType::Float3, "a_Position" },
			{ Enma::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);



		// Index Buffer
		unsigned int indices[3] = { 0,1,2 };

		Enma::Ref<Enma::IndexBuffer> indexBuffer = Enma::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		//Square--------------------------------------------------

		m_SquareVA = Enma::VertexArray::Create();


		float verticesSquare[5 * 4] = {
			-0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
			 0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
			 0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
			-0.75f,  0.75f, 0.0f, 0.0f, 1.0f
		};

		Enma::Ref<Enma::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer = Enma::VertexBuffer::Create(verticesSquare, sizeof(verticesSquare));

		squareVertexBuffer->SetLayout({
			{ Enma::ShaderDataType::Float3, "a_Position" },
			{ Enma::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVertexBuffer);

		unsigned int indicesSquare[6] = { 0, 1, 2, 2, 3, 0 };

		Enma::Ref<Enma::IndexBuffer> squareIndexBuffer = Enma::IndexBuffer::Create(indicesSquare, sizeof(indicesSquare) / sizeof(uint32_t));

		m_SquareVA->SetIndexBuffer(squareIndexBuffer);

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


		m_Shader = Enma::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);
		m_FlatColorShader = Enma::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		m_ZoroTexture = Enma::Texture2D::Create("assets/textures/zoro.png");


		textureShader->Bind();
		textureShader->SetInt("u_Texture", 0);

	}

	void ExampleLayer::OnAttach()
	{
	}

	void ExampleLayer::OnDetach()
	{
	}

	void ExampleLayer::OnUpdate(Enma::Timestep ts)
	{
		//Update
		m_CameraController.OnUpdte(ts);

		//Render
		Enma::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.5f });
		Enma::RenderCommand::Clear();


		Enma::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		m_FlatColorShader->Bind();
		m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				glm::vec3 pos(i * 0.18f, j * 0.18f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Enma::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_ZoroTexture->Bind();
		
		textureShader->Bind();
		Enma::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//Triangle render
		//Enma::Renderer::Submit(m_Shader, m_VertexArray);
		Enma::Renderer::EndScene();
	}

	void ExampleLayer::OnImGuiRender()
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void ExampleLayer::OnEvent(Enma::Event& e)
	{
		m_CameraController.OnEvent(e);

	}



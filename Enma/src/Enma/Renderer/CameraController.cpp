#include "empch.h"
#include "Enma/Renderer/CameraController.h"
#include "Enma/Core/Timestep.h"
#include "Enma/Core/Input.h"
#include "Enma/Core/MouseCodes.h"
#include "Enma/Core/Keycodes.h"
#include "Enma/Core/GamepadCodes.h"

namespace Enma
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_Rotation(rotation), m_Camera(- m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
	}

	void OrthographicCameraController::OnUpdte(Timestep deltaTime)
	{
		
		//EM_CORE_TRACE("Delta time: {0} s ({1} ms)", deltaTime.GetSeconds(), deltaTime.GetMilliseconds());

		if (Input::IsKeyPressed(Key::Up) || Input::IsKeyPressed(Key::W))
			m_CameraPosition.y += m_CameraTranslationSpeed * deltaTime;
		else if (Input::IsKeyPressed(Key::Down) || Input::IsKeyPressed(Key::S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * deltaTime;

		if (Input::IsKeyPressed(Key::Right) || Input::IsKeyPressed(Key::D))
			m_CameraPosition.x += m_CameraTranslationSpeed * deltaTime;
		else if (Input::IsKeyPressed(Key::Left) || Input::IsKeyPressed(Key::A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * deltaTime;

		if(m_Rotation)
		{
			if (Input::IsKeyPressed(Key::Q))
				m_CameraRotation += m_CameraRotationSpeed * deltaTime;
			else if (Input::IsKeyPressed(Key::E))
				m_CameraRotation -= m_CameraRotationSpeed * deltaTime;
			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel * 2;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(EM_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(EM_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.6f ;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.2f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;

	}
}
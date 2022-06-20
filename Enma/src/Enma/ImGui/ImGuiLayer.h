#pragma once

#include "Enma/Layer.h"

#include "Enma/Events/KeyEvent.h"
#include "Enma/Events/MouseEvent.h"
#include "Enma/Events/ApplicationEvent.h"

namespace Enma
{
	class ENMA_API ImGuiLayer : public Layer
	{
	public: 
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};

}


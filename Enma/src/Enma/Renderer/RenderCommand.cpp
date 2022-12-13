#include "empch.h"
#include "Enma/Renderer/RenderCommand.h"

namespace Enma
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
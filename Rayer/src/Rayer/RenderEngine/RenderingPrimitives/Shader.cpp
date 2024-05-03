
#include <Rayer/Core/Assert.h>
#include <Rayer/Renderer/Renderer.h>

#include "Shader.h"
#include <Platform/OpenGL/OpenGLShader.h>

namespace Rayer {

	Scope<Shader> Shader::Create(std::string vertexShaderPath, std::string fragmentShaderPath) {

		switch (Renderer::GetApi()) {

			case RendererApi::Api::None: RAYER_CORE_ASSERT(false, "RendererApi::None is not supported .") return nullptr;
			case RendererApi::Api::OpenGL: return CreateScope<OpenGLShader>(vertexShaderPath, fragmentShaderPath);

		}
	}

}
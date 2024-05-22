#include "RayerX.h"

namespace Rayer {


	RayerX::RayerX() {

		s_RendererApi = RenderEngine::GetActiveApi();

		// Creating shader for MeshBench
		m_Shader = Shader::Create("shader/rayerx/glsl/vertex.glsl", "shader/rayerx/glsl/fragment.glsl");
	}

	void RayerX::Init() {

		s_RendererApi->Init();

	}

	void RayerX::SetClearColor(const glm::vec4& color) {

		s_RendererApi->SetClearColor(color);

	}

	void RayerX::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {

		s_RendererApi->SetViewport(x, y, width, height);

	}

	void RayerX::Clear() {

		s_RendererApi->Clear();

	}

	void RayerX::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) {

		m_Shader->Bind();
		s_RendererApi->DrawIndexed(vertexArray, count);
		m_Shader->Unbind();

	}

	void RayerX::DrawWireframe(const Ref<VertexArray>& vertexArray, uint32_t count) {
		m_Shader->Bind();
		s_RendererApi->DrawWireframe(vertexArray, count);
		m_Shader->Unbind();
	}

	void RayerX::DrawLine(const Ref<VertexArray>& vertexArray, uint32_t count) {

		m_Shader->Bind();
		s_RendererApi->DrawLine(vertexArray, count);
		m_Shader->Unbind();
	}


	// Uniform setting functions implementation
	void RayerX::SetShaderMat4(const std::string& name, const glm::mat4& matrix) {
		m_Shader->Bind();
		m_Shader->SetUniformMat4(name, matrix);
		m_Shader->Unbind();
	}

	void RayerX::SetShaderFloat(const std::string& name, float value) {
		m_Shader->Bind();
		m_Shader->SetUniformFloat(name, value);
		m_Shader->Unbind();
	}

	void RayerX::SetShaderFloat3(const std::string& name, const glm::vec3& value) {

		m_Shader->Bind();
		m_Shader->SetUniformFloat3(name, value);
		m_Shader->Unbind();
	}

	void RayerX::SetShaderFloat4(const std::string& name, const glm::vec4& value) {

		m_Shader->Bind();
		m_Shader->SetUniformFloat4(name, value);
		m_Shader->Unbind();
	}

	void RayerX::SetShaderInt(const std::string& name, int value) {
		m_Shader->Bind();
		m_Shader->SetUniformInt(name, value);
		m_Shader->Unbind();
	}

	void RayerX::SetShaderUnsignedInt(const std::string& name, unsigned int value) {
		m_Shader->Bind();
		m_Shader->SetUniformUnsignedInt(name , value);
		m_Shader->Unbind();
	}

	void RayerX::SetShaderBool(const std::string& name, bool value) {
		m_Shader->Bind();
		m_Shader->SetUniformBool(name, value);
		m_Shader->Unbind();
	}



}
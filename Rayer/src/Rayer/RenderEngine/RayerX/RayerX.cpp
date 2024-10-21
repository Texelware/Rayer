#include "RayerX.h"

namespace Rayer {


	RayerX::RayerX() {

		s_RendererApi = RenderEngine::GetActiveApi();

		// Creating shader for RayerX
		m_Shader = Shader::Create("shader/rayerx/glsl/default/vertex.glsl", "shader/rayerx/glsl/default/fragment.glsl");
		m_ShaderSkybox = Shader::Create("shader/rayerx/glsl/skybox/vertex.glsl", "shader/rayerx/glsl/skybox/fragment.glsl");
		m_ShaderShadow = Shader::Create("shader/rayerx/glsl/shadow/vertex.glsl", "shader/rayerx/glsl/shadow/fragment.glsl");

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

	void RayerX::ClearDepth() {

		s_RendererApi->ClearDepth();

	}

	void RayerX::BindTextureToUnit(uint32_t slot, uint32_t texID) {

		s_RendererApi->BindTextureToUnit(slot, texID);

	}

	void RayerX::DrawSkybox(const Ref<VertexArray>& vertexArray, uint32_t count) {

		m_ShaderSkybox->Bind();
		s_RendererApi->DrawSkybox(vertexArray, count);
		m_ShaderSkybox->Unbind();

	}

	void RayerX::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) {

		m_Shader->Bind();
		s_RendererApi->DrawIndexed(vertexArray, count);
		m_Shader->Unbind();

	}

	void RayerX::DrawShadows(const Ref<VertexArray>& vertexArray, uint32_t count) {

		m_ShaderShadow->Bind();
		s_RendererApi->DrawIndexed(vertexArray, count);
		m_ShaderShadow->Unbind();

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
	void RayerX::SetShaderMat4(RayerXShaderType type,const std::string& name, const glm::mat4& matrix) {

		switch (type) {

		case RayerXShaderType::Default:
			m_Shader->Bind();
			m_Shader->SetUniformMat4(name, matrix);
			m_Shader->Unbind();
			break;

		case RayerXShaderType::Skybox:

			m_ShaderSkybox->Bind();
			m_ShaderSkybox->SetUniformMat4(name, matrix);
			m_ShaderSkybox->Unbind();
			break;

		case RayerXShaderType::Shadow:
			
			m_ShaderShadow->Bind();
			m_ShaderShadow->SetUniformMat4(name, matrix);
			m_ShaderShadow->Unbind();
			break;

		}
	}

	

	void RayerX::SetShaderFloat(RayerXShaderType type,const std::string& name, float value) {
		

		switch (type)
		{
		case RayerXShaderType::Default:
			m_Shader->Bind();
			m_Shader->SetUniformFloat(name, value);
			m_Shader->Unbind();
			break;

		case RayerXShaderType::Skybox:

			m_ShaderSkybox->Bind();
			m_ShaderSkybox->SetUniformFloat(name, value);
			m_ShaderSkybox->Unbind();
			break;

		case RayerXShaderType::Shadow:

			m_ShaderShadow->Bind();
			m_ShaderShadow->SetUniformFloat(name, value);
			m_ShaderShadow->Unbind();
			break;
		}
	}

	void RayerX::SetShaderFloat3(RayerXShaderType type,const std::string& name, const glm::vec3& value) {

		switch (type)
		{
		case RayerXShaderType::Default:
			m_Shader->Bind();
			m_Shader->SetUniformFloat3(name, value);
			m_Shader->Unbind();
			break;

		case RayerXShaderType::Skybox:

			m_ShaderSkybox->Bind();
			m_ShaderSkybox->SetUniformFloat3(name, value);
			m_ShaderSkybox->Unbind();
			break;

		case RayerXShaderType::Shadow:

			m_ShaderShadow->Bind();
			m_ShaderShadow->SetUniformFloat3(name, value);
			m_ShaderShadow->Unbind();
			break;
		}
	}

	void RayerX::SetShaderFloat4(RayerXShaderType type,const std::string& name, const glm::vec4& value) {

		switch (type)
		{
		case RayerXShaderType::Default:
			m_Shader->Bind();
			m_Shader->SetUniformFloat4(name, value);
			m_Shader->Unbind();
			break;

		case RayerXShaderType::Skybox:

			m_ShaderSkybox->Bind();
			m_ShaderSkybox->SetUniformFloat4(name, value);
			m_ShaderSkybox->Unbind();
			break;

		case RayerXShaderType::Shadow:

			m_ShaderShadow->Bind();
			m_ShaderShadow->SetUniformFloat4(name, value);
			m_ShaderShadow->Unbind();
			break;
		}
	}

	void RayerX::SetShaderInt(RayerXShaderType type,const std::string& name, int value) {
		switch (type)
		{
		case RayerXShaderType::Default:
			m_Shader->Bind();
			m_Shader->SetUniformInt(name, value);
			m_Shader->Unbind();
			break;

		case RayerXShaderType::Skybox:

			m_ShaderSkybox->Bind();
			m_ShaderSkybox->SetUniformInt(name, value);
			m_ShaderSkybox->Unbind();
			break;

		case RayerXShaderType::Shadow:

			m_ShaderShadow->Bind();
			m_ShaderShadow->SetUniformInt(name, value);
			m_ShaderShadow->Unbind();
			break;
		}
	}



	void RayerX::SetShaderUnsignedInt(RayerXShaderType type,const std::string& name, unsigned int value) {
		switch (type)
		{
		case RayerXShaderType::Default:
			m_Shader->Bind();
			m_Shader->SetUniformUnsignedInt(name, value);
			m_Shader->Unbind();
			break;

		case RayerXShaderType::Skybox:

			m_ShaderSkybox->Bind();
			m_ShaderSkybox->SetUniformUnsignedInt(name, value);
			m_ShaderSkybox->Unbind();
			break;

		case RayerXShaderType::Shadow:

			m_ShaderShadow->Bind();
			m_ShaderShadow->SetUniformUnsignedInt(name, value);
			m_ShaderShadow->Unbind();
			break;
		}
	}

	void RayerX::SetShaderBool(RayerXShaderType type,const std::string& name, bool value) {
		
		switch (type)
		{
		case RayerXShaderType::Default:
			m_Shader->Bind();
			m_Shader->SetUniformBool(name, value);
			m_Shader->Unbind();
			break;

		case RayerXShaderType::Skybox:

			m_ShaderSkybox->Bind();
			m_ShaderSkybox->SetUniformBool(name, value);
			m_ShaderSkybox->Unbind();
			break;

		case RayerXShaderType::Shadow:

			m_ShaderShadow->Bind();
			m_ShaderShadow->SetUniformBool(name, value);
			m_ShaderShadow->Unbind();
			break;
		}
	}



}
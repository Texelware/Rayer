#pragma once

#include <Rayer/Core/Core.h>
#include <Rayer/RenderEngine/RendererApi.h>
#include <Rayer/RenderEngine/RenderEngine.h>
#include <Rayer/RenderEngine/RenderingPrimitives/Shader.h>
#include <Rayer/RenderEngine/RenderingPrimitives/Framebuffer.h>


enum class RayerXShaderType {

	None,
	Default,
	Skybox,
	Shadow

};

namespace Rayer {

	class RayerX : public RenderEngine {

	public:

		RayerX();

		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void Clear() override;
		void ClearDepth();

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) override;
		void DrawShadows(const Ref<VertexArray>& vertexArray, uint32_t count);

		virtual void DrawWireframe(const Ref<VertexArray>& vertexArray, uint32_t count) override;
		virtual void DrawLine(const Ref<VertexArray>& vertexArray, uint32_t count) override;

		void DrawSkybox(const Ref<VertexArray>& vertexArray, uint32_t count);

		// Uniform setting functions
		void SetShaderMat4(RayerXShaderType type , const std::string& name, const glm::mat4& matrix);
		
		void SetShaderFloat(RayerXShaderType type,const std::string& name, float value);
		void SetShaderFloat3(RayerXShaderType type,const std::string& name, const glm::vec3& value);
		void SetShaderFloat4(RayerXShaderType type,const std::string& name, const glm::vec4& value);
		void SetShaderInt(RayerXShaderType type,const std::string& name, int value);

		
		void SetShaderUnsignedInt(RayerXShaderType type,const std::string& name, unsigned int value);
		void SetShaderBool(RayerXShaderType type,const std::string& name, bool value);


		void BindTextureToUnit(uint32_t slot , uint32_t texID);

	private:
			
		Ref<RendererApi> s_RendererApi;

		// RayerX related shader
		Scope<Shader> m_Shader;
		Scope<Shader> m_ShaderSkybox;
		Scope<Shader> m_ShaderShadow;

	};

}
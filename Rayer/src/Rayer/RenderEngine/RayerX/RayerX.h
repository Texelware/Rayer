#pragma once

#include <Rayer/Core/Core.h>
#include <Rayer/RenderEngine/RendererApi.h>
#include <Rayer/RenderEngine/RenderEngine.h>
#include <Rayer/RenderEngine/RenderingPrimitives/Shader.h>
#include <Rayer/RenderEngine/RenderingPrimitives/Framebuffer.h>


namespace Rayer {

	class RayerX : public RenderEngine {

	public:

		RayerX();

		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) override;
		virtual void DrawWireframe(const Ref<VertexArray>& vertexArray, uint32_t count) override;
		virtual void DrawLine(const Ref<VertexArray>& vertexArray, uint32_t count) override;

		// Uniform setting functions
		void SetShaderMat4(const std::string& name, const glm::mat4& matrix);
		void SetShaderFloat(const std::string& name, float value);

		void SetShaderInt(const std::string& name, int value);
		void SetShaderBool(const std::string& name, bool value);

	private:
			
		Ref<RendererApi> s_RendererApi;

		// RayerX related shader
		Scope<Shader> m_Shader;

	};

}
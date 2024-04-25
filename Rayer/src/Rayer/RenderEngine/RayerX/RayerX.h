#pragma once
#include <Rayer/RenderEngine/RenderEngine.h>


namespace Rayer {

	class RayerX : public RenderEngine {

	public:

		RayerX();

		virtual void SetClearColor(const glm::vec4& color) override;

		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) override;

	private:
			
		Ref<RendererApi> s_RendererApi;


	};

}
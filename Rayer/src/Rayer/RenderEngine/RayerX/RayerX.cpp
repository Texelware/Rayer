#include <Rayer/RenderEngine/RayerX/RayerX.h>


namespace Rayer {


	RayerX::RayerX() {

		s_RendererApi = RenderEngine::GetActiveApi();
	}

	void RayerX::SetClearColor(const glm::vec4& color) {

		s_RendererApi->SetClearColor(color);

	}

	void RayerX::Clear() {

		s_RendererApi->Clear();

	}

	void RayerX::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) {

		s_RendererApi->DrawIndexed(vertexArray, count);

	}


}
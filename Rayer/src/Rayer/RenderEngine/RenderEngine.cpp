#include <Rayer/RenderEngine/RenderEngine.h>


namespace Rayer {

	Ref<RendererApi> RenderEngine::s_RendererApi = RendererApi::Create();

}
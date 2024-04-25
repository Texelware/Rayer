#pragma once

#include <Rayer/RenderEngine/RendererApi.h>

namespace Rayer {


	class Renderer {

		public:
			
			void Begin();
			void End();

			void Submit();

			static RendererApi::Api GetApi() { return RendererApi::GetApi(); }
			
	};

}
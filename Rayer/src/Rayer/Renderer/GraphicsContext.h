#pragma once


namespace Rayer {

	//Graphics context interface => All graphics api should create a graphics context using this interface(eg. OpenGL, Vulkan, etc)
	class IGraphicsContext {

		public:

			virtual void Init() = 0;
			virtual void SwapBuffers() = 0;
	};

}
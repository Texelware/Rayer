#pragma once
#include <rpch.h>
#include <glad/glad.h>
#include <glfw3.h>
#include <Rayer/Renderer/GraphicsContext.h>


namespace Rayer {


	class OpenGLContext : public IGraphicsContext {

	public:

		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:

		GLFWwindow* _windowHandle;

	};

}
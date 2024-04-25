
#include "OpenGLContext.h"

namespace Rayer {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : _windowHandle(windowHandle){}

	void OpenGLContext::Init() {

		glfwMakeContextCurrent(_windowHandle);
		
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		
		if (!status) {

			std::cerr << "Failed to initialize OpenGL context(GLAD) ." << std::endl;
			glfwDestroyWindow(_windowHandle);
			glfwTerminate();
			exit(EXIT_FAILURE);
		}



	}


	void OpenGLContext::SwapBuffers() {

		glfwSwapBuffers(_windowHandle);

	}

}
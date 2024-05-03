
#include <Rayer/Core/Core.h>
#include <Rayer/Core/Application.h>
#include <Rayer/Core/Input.h>

#include <glfw3.h>

namespace Rayer {

	bool Input::IsKeyPressed(const KeyCode key) {

		GLFWwindow* window = static_cast<RAYER_WINDOW*>(Application::Get().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS;

	}

	bool Input::IsMouseButtonPressed(const MouseCode button) {

		GLFWwindow* window = static_cast<RAYER_WINDOW*>(Application::Get().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));

		return state == GLFW_PRESS;

	}

	glm::vec2 Input::GetMousePosition() {


			GLFWwindow* window = static_cast<RAYER_WINDOW*>(Application::Get().GetNativeWindow());

			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			glm::vec2 mousePosition = glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos));

			return mousePosition;

	}

	float Input::GetMouseX() {

		return GetMousePosition().x;

	}

	float Input::GetMouseY() {

		return GetMousePosition().y;
	}


}
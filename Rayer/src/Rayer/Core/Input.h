#pragma once
#include "KeyCodes.h"
#include "MouseCodes.h"

#include <glm/glm.hpp>

namespace Rayer {

	class Input {

	public :
		static bool IsKeyPressed(const KeyCode key);
		
		static bool IsMouseButtonPressed(const MouseCode button);

		static glm::vec2 GetMousePosition();

		static float GetMouseX();
		static float GetMouseY();


	};

}
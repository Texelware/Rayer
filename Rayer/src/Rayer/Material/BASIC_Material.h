#pragma once

#include "Material.h"

#include <glm/glm.hpp>

namespace Rayer {

	class BASIC_Material : public Material {

	public:

		BASIC_Material();

		virtual void Reset() override;

		glm::vec4& GetColor() { return _color; }

	private:

		glm::vec4 _color { 1.0f, 1.0f, 1.0f, 1.0f };

	};

}
#pragma once

#include <Rayer/Component/Component.h>

#include <glm/glm.hpp>


namespace Rayer {

	class TransformComponent : public Component {

	public:

		TransformComponent(glm::mat4& _modelMatrix);

		virtual void OnUpdate() override;
		virtual void OnRender() override;

		glm::mat4& GetTransformationMatrix() {

			return transformationMatrix;
		}

	private:
		
		glm::mat4& modelMatrix;

		glm::vec3 translate;
		glm::vec3 rotation{ 0.0f , 0.0f , 0.0f};
		glm::vec3 scale;

		
		glm::mat4 transformationMatrix{ glm::mat4(1) };

	};

}

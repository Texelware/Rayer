#pragma once

#include <Rayer/Component/Component.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Rayer {

	class TransformComponent : public Component {

	public:

		TransformComponent(glm::mat4& _modelMatrix);

		virtual void OnUpdate() override;
		virtual void OnRender() override;

		glm::mat4& GetTransformationMatrix() {

			return transformationMatrix;
		}

		glm::vec3 GetPosition() {

			return glm::vec3(modelMatrix[3]);

		}

		glm::vec3 GetScale() {

			float scaleX = glm::length(glm::vec3(modelMatrix[0]));  // First column
			float scaleY = glm::length(glm::vec3(modelMatrix[1]));  // Second column
			float scaleZ = glm::length(glm::vec3(modelMatrix[2]));  // Third column

			return glm::vec3(scaleX, scaleY, scaleZ);

		}



		//-------------Setter Methods------------------

		void SetPosition(const glm::vec3 position) {

			translate = position;
		}

		void SetScale(const glm::vec3 scaleFactor) {

			scale = scaleFactor;

		}



	private:
		
		glm::mat4& modelMatrix;

		glm::vec3 translate;
		glm::vec3 rotation{ 0.0f , 0.0f , 0.0f};
		glm::vec3 scale;

		
		glm::mat4 transformationMatrix{ glm::mat4(1) };

	};

}

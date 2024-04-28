#pragma once
#include <rpch.h>
#include <Rayer/Core/Core.h>

#include <glm/glm.hpp>


namespace Rayer {

	struct Vertex {

		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;

	};

	//Mesh structure to store vertices , normals , indices etc.
	struct Mesh {

		std::vector<Vertex> vertices {};
		std::vector<unsigned int> indices {};

	};

	
	class Model {

		Model(std::string _name,Mesh& _mesh);

		std::string GetModelName() const;
		std::vector<Mesh>& GetMeshes() ;

	private:

		std::vector<Mesh> meshes;

		std::string modelName;

	};

}
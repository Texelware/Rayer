#pragma once
#include <rpch.h>
#include <Rayer/Core/Core.h>


namespace Rayer {

	//Mesh structure to store vertices , normals , indices etc.
	struct Mesh {

		std::vector<float> vertices {};
		std::vector<unsigned int> indices {};

	};


	
	class Model {

		Model(std::string _name,Mesh& _mesh);

		std::string GetModelName() const;
		Ref<Mesh> GetMesh() const;

	private:

		Ref<Mesh> mesh;

		std::string modelName;

	};

}
#include "Model.h"


namespace Rayer {

	Model::Model(std::string _name, Mesh& _mesh) : modelName(_name) {}

	std::string Model::GetModelName() const {

		return modelName;

	}

	std::vector<Mesh>& Model::GetMeshes()  {

		return meshes;
	}

}
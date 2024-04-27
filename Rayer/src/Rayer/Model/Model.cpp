#include "Model.h"


namespace Rayer {

	Model::Model(std::string _name, Mesh& _mesh) : modelName(_name), mesh(CreateRef<Mesh>(_mesh)) {}

	std::string Model::GetModelName() const {

		return modelName;

	}

	Ref<Mesh> Model::GetMesh() const {

		return mesh;
	}

}
#include "Model.h"


namespace Rayer {

	Model::Model(const std::string& _name ,const std::filesystem::path& filepath) : modelName(_name) {

		LoadModel(filepath);

	}

	std::string Model::GetModelName() const {

		return modelName;

	}

	std::vector<Mesh>& Model::GetMeshes()  {

		return meshes;
	}

}
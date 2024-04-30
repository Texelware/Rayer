#include "Model.h"


namespace Rayer {

	Model::Model(const std::string& _name ,const std::filesystem::path& filepath) : modelName(_name) {

		LoadModel(filepath);

        // Convert vertices to a flat array of floats
        std::vector<float> vertexData;
        for (const auto& mesh : meshes) {
            for (const auto& vertex : mesh.vertices) {
                // Add position
                vertexData.push_back(vertex.position.x);
                vertexData.push_back(vertex.position.y);
                vertexData.push_back(vertex.position.z);

                // Add normal
                //vertexData.push_back(vertex.normal.x);
                //vertexData.push_back(vertex.normal.y);
                //vertexData.push_back(vertex.normal.z);

                // Add texture coordinates
                //vertexData.push_back(vertex.texCoords.x);
                //vertexData.push_back(vertex.texCoords.y);
            }
        }


        std::vector<uint32_t> indexData;
        for (const auto& mesh : meshes) {
            for (const auto& index : mesh.indices) {
                indexData.push_back(index);
            }
        }


        // Create a VertexBuffer using the vertex data
        vertexBuffer = VertexBuffer::Create(vertexData.data(), static_cast<uint32_t>(vertexData.size() * sizeof(float)));
        // Create an IndexBuffer using the index data
        indexBuffer = IndexBuffer::Create(indexData.data(), static_cast<uint32_t>(indexData.size()));
	}

	std::string Model::GetModelName() const {

		return modelName;

	}

	std::vector<Mesh>& Model::GetMeshes()  {

		return meshes;
	}


    uint32_t Model::GetTotalIndexCount() const {
        unsigned int totalCount = 0;
        for (const auto& mesh : meshes) {
            totalCount += static_cast<uint32_t>(mesh.indices.size());
        }
        return totalCount;
    }
}
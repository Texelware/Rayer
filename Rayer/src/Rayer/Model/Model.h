#pragma once
#include <rpch.h>
#include <Rayer/Core/Core.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Rayer/RenderEngine/RenderingPrimitives/Buffer.h>

//assimp model loader headers
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>

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

	public:
		Model(const std::string& _name ,const std::filesystem::path& filepath);

		std::string GetModelName() const;
		std::vector<Mesh>& GetMeshes() ;

		bool IsReadSuccessful() const { return readStatus; }

		Ref<VertexBuffer>& GetVertexBuffer() { return vertexBuffer; }
		Ref<IndexBuffer>& GetIndexBuffer() { return indexBuffer; }

		glm::mat4& GetModelMatrix() { return modelMatrix; }
		uint32_t GetTotalIndexCount() const;

	private:

		std::vector<Mesh> meshes;

		std::string modelName;

		//The model matrix for the model .
		glm::mat4 modelMatrix {glm::mat4(1)};

		//Data read status from the model file
		bool readStatus = false;

		Ref<VertexBuffer> vertexBuffer;
		Ref<IndexBuffer> indexBuffer;


		////////////////////////////////////////////////
		//////////////Mesh Processing//////////////////
		//////////////////////////////////////////////

		void LoadModel(const std::filesystem::path& filepath);

		void ProcessNode(aiNode* node, const aiScene* scene);

		Mesh ProcessMesh(aiMesh* mesh);

	};

}
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

		void LoadModel(const std::filesystem::path& filepath) {

			Assimp::Importer importer;

			const aiScene* scene = importer.ReadFile(filepath.string(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_ConvertToLeftHanded);

			//Error checking
			if (scene == nullptr) {

				std::cerr << "Model Loading Failed : "<<importer.GetErrorString() << std::endl;
				return;
			}

			//Set the read status to true .
			readStatus = true;

			ProcessNode(scene->mRootNode, scene);


			
		}

		void ProcessNode(aiNode* node, const aiScene* scene) {

			// Process all the node's meshes (if any)
			for (unsigned int i = 0; i < node->mNumMeshes; ++i) {

				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				meshes.push_back(ProcessMesh(mesh));

			}

			//Process each nodes cchildren recursively
			for (unsigned int i = 0; i < node->mNumChildren; ++i) {

				ProcessNode(node->mChildren[i], scene);

			}

			return;
			
		}


		Mesh ProcessMesh(aiMesh* mesh) {

			Mesh result;

			for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {

				Vertex vert;

				//Process vertex positions
				vert.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

				//Process vertex normals (if any)
				if (mesh->HasNormals()) {

					vert.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

				}

				//Process vertex texture coordinates (if any)
				if (mesh->HasTextureCoords(0)) {

					vert.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

				}

				result.vertices.push_back(vert);

			}

			for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {

				aiFace face = mesh->mFaces[i];

				for (unsigned int j = 0; j < face.mNumIndices; ++j) {

					result.indices.push_back(face.mIndices[j]);

				}

			}

			

			return result;

		}


	};

}
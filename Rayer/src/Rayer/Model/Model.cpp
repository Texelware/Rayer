#include "Model.h"



namespace Rayer {

	Model::Model(const std::string& _name ,const int id, const EntityType type ,const std::filesystem::path& filepath) : Entity(_name, id , type) {

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
                vertexData.push_back(vertex.normal.x);
                vertexData.push_back(vertex.normal.y);
                vertexData.push_back(vertex.normal.z);

                // Add texture coordinates
                vertexData.push_back(vertex.texCoords.x);
                vertexData.push_back(vertex.texCoords.y);
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

       
        AddComponent(new TransformComponent(modelMatrix));
        //AddComponent(new MaterialComponent());



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




    void Model::LoadModel(const std::filesystem::path& filepath) {

        Assimp::Importer importer;

        //const aiScene* scene = importer.ReadFile(filepath.string(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_ConvertToLeftHanded);
        const aiScene* scene = importer.ReadFile(filepath.string(),
            aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

        //Error checking
        if (scene == nullptr) {

            std::cerr << "Model Loading Failed : " << importer.GetErrorString() << std::endl;
            
            return;
        }

        //Set the read status to true .
        readStatus = true;

        ProcessNode(scene->mRootNode, scene);



    }


    void Model:: ProcessNode(aiNode* node, const aiScene* scene) {

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



    Mesh Model::ProcessMesh(aiMesh* mesh) {

        Mesh result;

        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {

            Vertex vert;

            //Process vertex positions
            vert.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            //Process vertex normals
            vert.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

            //Process vertex texture coordinates (if any)
            if (mesh->HasTextureCoords(0)) {

                vert.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

            }

            else {

                vert.texCoords = glm::vec2(0.0f, 0.0f);

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
}
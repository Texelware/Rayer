#pragma once

#include <rpch.h>
#include <Rayer/Core/Core.h>
#include <Rayer/Core/Entity.h>
#include "SceneSerializer.h"


namespace Rayer {


	enum SerializeState {

		Serialized,
		NotSerialized
	};

	class Scene {

	public:

		Scene();

		static std::string selectedEntityName;
		static int selectedEntityID;

		//Refrence to the directional light
		static Ref<Entity> directionalLight;

		//Light count
		static int directionalLightCount;
		static int pointLightCount;
		static int spotLightCount;
		

		static int nextEntityID;

		//Iterator for models of the scene .
		template <typename T>
		using interator = std::vector<Ref<T>>::iterator;
		template <typename T>
		using const_interator = std::vector<Ref<T>>::const_iterator;

		//For non const iterators
		interator<Entity> getEntityIteratorBegin()  { return m_Entities.begin(); }
		interator<Entity> getEntityIteratorEnd()  { return m_Entities.end(); }

		//For const iterators
		const_interator<Entity> getEntityIteratorBeginC() const { return m_Entities.begin(); }
		const_interator<Entity> getEntityIteratorEndC() const { return m_Entities.end(); }

		SceneSerializer* getSerializer() { 

			return sceneSerializer.get(); 
		}

		SerializeState getSceneSerializeState() { return serializeState; }
		
		void setSceneSerializeState(const SerializeState state) {

			serializeState = state;

		}

		std::filesystem::path& getSerializedPath() { return serializedPath; }
		void setSerializedPath(const std::filesystem::path& path) { serializedPath = path; }

		void AddEntity(Ref<Entity>& entity);
		void RemoveEntity(int entityID);

		void ClearScene();


	private:
		
		std::vector<Ref<Entity>> m_Entities {};

		//SceneSerializer for serialization and deserialization
		std::unique_ptr<SceneSerializer> sceneSerializer = nullptr;

		SerializeState serializeState { NotSerialized };

		std::filesystem::path serializedPath {};

	};

}
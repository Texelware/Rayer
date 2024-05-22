#pragma once

#include <rpch.h>
#include <Rayer/Core/Core.h>
#include <Rayer/Core/Entity.h>


namespace Rayer {


	class Scene {

	public:

		static std::string selectedEntityName;
		static int selectedEntityID;


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



		void AddEntity(Ref<Entity>& entity);
		void RemoveEntity(int entityID);

	private:

		std::vector<Ref<Entity>> m_Entities {};

	};

}
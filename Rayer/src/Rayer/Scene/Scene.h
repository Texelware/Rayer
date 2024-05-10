#pragma once

#include <rpch.h>
#include <Rayer/Core/Core.h>
#include <Rayer/Model/Model.h>


namespace Rayer {


	class Scene {

	public:

		static std::string selectedObjectName;

		//Iterator for models of the scene .
		template <typename T>
		using model_interator = std::vector<Ref<T>>::iterator;
		template <typename T>
		using const_model_interator = std::vector<Ref<T>>::const_iterator;

		//For non const iterators
		model_interator<Model> getModelIteratorBegin()  { return m_Models.begin(); }
		model_interator<Model> getModelIteratorEnd()  { return m_Models.end(); }

		//For const iterators
		const_model_interator<Model> getModelIteratorBeginC() const { return m_Models.begin(); }
		const_model_interator<Model> getModelIteratorEndC() const { return m_Models.end(); }



		void AddModel(Ref<Model>& model);

	private:

		std::vector<Ref<Model>> m_Models {};

	};

}
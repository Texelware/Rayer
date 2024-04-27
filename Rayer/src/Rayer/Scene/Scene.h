#pragma once

#include <rpch.h>
#include <Rayer/Core/Core.h>
#include <Rayer/Model/Model.h>


namespace Rayer {


	class Scene {

	public:


		//Iterator for models of the scene .
		using model_interator = std::vector<Ref<Model>>::iterator;
		using const_model_interator = std::vector<Ref<Model>>::const_iterator;

		//For non const iterators
		model_interator getModelIteratorBegin()  { return m_Models.begin(); }
		model_interator getModelIteratorEnd()  { return m_Models.end(); }

		//For const iterators
		const_model_interator getModelIteratorBeginC() const { return m_Models.begin(); }
		const_model_interator getModelIteratorEndC() const { return m_Models.end(); }


	private:

		std::vector<Ref<Model>> m_Models {};

	};

}
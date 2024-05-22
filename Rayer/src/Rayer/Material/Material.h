#pragma once


namespace Rayer {

	enum class MaterialType {

		NONE = 0,
		PBR,
		BASIC

	};

	class Material {

	public:

		
		Material(MaterialType type) : m_type(type) {}

		virtual ~Material() {}
		MaterialType GetMaterialType() const { return m_type; }

		virtual void Reset() = 0;

	private:

		MaterialType m_type;

	};

}
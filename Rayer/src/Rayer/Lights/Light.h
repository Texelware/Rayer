#pragma once
#include <Rayer/Core/Entity.h>

#define NUM_MAX_DIRECTIONAL_LIGHT 1

#define NUM_MAX_POINT_LIGHT 10

#define NUM_MAX_SPOT_LIGHT 10




namespace Rayer {

	enum class LightType {

		None = 0,
		Directional,
		Point,
		Spot,
		Area,
		SkyLight

	};

	class Light : public Entity {

	public:

		Light(LightType type , std::string name , const int entity_id );

		LightType GetLightType() const { return m_type; }


	private:

		LightType m_type;

	};

}
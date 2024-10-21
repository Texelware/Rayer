#pragma once
#include <rpch.h>

namespace Rayer {

	enum class ComponentType {

		None = 0,
		TransformComponent,
		CameraComponent,
		MaterialComponent,
		SkyLightComponent,
		LightComponent

	};


	class Component {

	public:

		Component() = delete;
		Component(ComponentType _type) : type(_type) {}

		virtual ~Component() {}

		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;

		ComponentType GetComponentType() const { return type; }

		
	private:

		ComponentType type = ComponentType::None;

	 
	};

}
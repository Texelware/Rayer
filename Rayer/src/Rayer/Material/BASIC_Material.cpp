
#include "BASIC_Material.h"


namespace Rayer {


	BASIC_Material::BASIC_Material() : Material(MaterialType::BASIC) {



	}

	void BASIC_Material::Reset() {

		_color = { 1.0f, 1.0f, 1.0f, 1.0f };
	}



}
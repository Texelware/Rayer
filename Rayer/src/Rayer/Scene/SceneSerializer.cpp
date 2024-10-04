#include "SceneSerializer.h"
#include "Scene.h"
#include <toml++/toml.h>
#include <Rayer/Log/Logger.h>
#include <Rayer/Model/Model.h>

#include <Rayer/Component/LightComponent.h>

namespace Rayer {

	// Function to replace single backslashes with double backslashes
	std::string EscapeBackslashes(const std::string& path) {
		std::string escapedPath = path;

		// First, replace all single backslashes with forward slashes
		std::replace(escapedPath.begin(), escapedPath.end(), '\\', '/');

		return escapedPath;
	}


	SceneSerializer::SceneSerializer(Scene* scene) : mScene(scene) {

	}

	void SceneSerializer::Serialize(const std::filesystem::path& filepath) {

		// Get the iterators for the entities in the scene
		auto entityBegin = mScene->getEntityIteratorBeginC();
		auto entityEnd = mScene->getEntityIteratorEndC();

		LogManager* logManager = LogManager::Get();

		toml::table data;

		for (auto it = entityBegin; it != entityEnd; ++it) {

			try {


				data.insert("scene", filepath.filename().stem().string());

				toml::table entity;

				entity.insert("id", it->get()->GetEntityID());
				entity.insert("name", it->get()->GetEntityName());

				Ref<Entity> sceneEntity = *it;

				switch (sceneEntity->GetEntityType()) {

				case EntityType::Model: {

					entity.insert("type", "model");

					entity.insert("model_path", EscapeBackslashes(std::dynamic_pointer_cast<Model>(sceneEntity)->GetModelPath().string()));




					if (sceneEntity->HasComponent(ComponentType::TransformComponent)) {

						toml::table transform;

						Component* comp = sceneEntity->GetComponent(ComponentType::TransformComponent);

						TransformComponent* transformComp = dynamic_cast<TransformComponent*>(comp);

						glm::vec3 pos = transformComp->GetPosition();
						glm::vec3 scale = transformComp->GetScale();

						transform.insert("position", toml::array(pos.x, pos.y, pos.z));
						transform.insert("scale", toml::array(scale.x, scale.y, scale.z));


						entity.insert("transform", transform);

					}

					/////////////////////////////////////////////////////////////////
					///////////////////////////////Material Component Check/////////
					////////////////////////////////////////////////////////////////

					if (sceneEntity->HasComponent(ComponentType::MaterialComponent)) {

						toml::table material;

						Component* comp = sceneEntity->GetComponent(ComponentType::MaterialComponent);

						MaterialComponent* matComp = dynamic_cast<MaterialComponent*>(comp);

						switch (matComp->GetMaterial()->GetMaterialType()) {

						case MaterialType::PBR: {

							material.insert("type", "pbr");

							Ref<PBR_Material> pbrMat = dynamic_pointer_cast<PBR_Material>(matComp->GetMaterial());

							toml::table textures;

							////////////////////////////////////////////////////////////
							////////////Checking texture maps//////////////////////////
							///////////////////////////////////////////////////////////

							if (pbrMat && pbrMat->GetTextureAvailabilityStatus().has_albedo) {

								textures.insert("albedo",
									EscapeBackslashes(pbrMat->GetTexturePaths().albedo_path.string()));

							}

							if (pbrMat && pbrMat->GetTextureAvailabilityStatus().has_normal) {

								textures.insert("normal",
									EscapeBackslashes(pbrMat->GetTexturePaths().normal_path.string()));

							}

							if (pbrMat && !pbrMat->GetTextureAvailabilityStatus().has_albedo) {

								textures.insert("albedo", "none");

							}

							if (pbrMat && !pbrMat->GetTextureAvailabilityStatus().has_normal) {

								textures.insert("normal", "none");

							}

							material.insert("textures", textures);

							////////////////////////////////////////////////////////////
							//////End of checking texture maps//////////////////////////
							///////////////////////////////////////////////////////////

							break;
						}

						case MaterialType::BASIC: {

							material.insert("type", "basic");

							Ref<BASIC_Material> basicMat = dynamic_pointer_cast<BASIC_Material>(matComp->GetMaterial());

							toml::table properties;

							glm::vec4 color = basicMat->GetColor();
							properties.insert("color", toml::array(color.r, color.g, color.b, color.a));

							material.insert("properties", properties);

							break;
						}

						default: {

							material.insert("type", "default");
							break;
						}


						}

						entity.insert("material", material);


					}

					if (!sceneEntity->HasComponent(ComponentType::MaterialComponent)) {

						toml::table material;

						material.insert("type", "default");

						entity.insert("material", material);
					}

					/////////////////////////////////////////////////////////////////
					////////////////////////End of Material Component Check/////////
					////////////////////////////////////////////////////////////////

					break;
				}


				case EntityType::Light: {

					entity.insert("type", "light");

					if (sceneEntity->HasComponent(ComponentType::TransformComponent)) {

						toml::table transform;

						Component* comp = sceneEntity->GetComponent(ComponentType::TransformComponent);

						TransformComponent* transformComp = dynamic_cast<TransformComponent*>(comp);

						glm::vec3 pos = transformComp->GetPosition();
						glm::vec3 scale = transformComp->GetScale();

						transform.insert("position", toml::array(pos.x, pos.y, pos.z));
						transform.insert("scale", toml::array(scale.x, scale.y, scale.z));


						entity.insert("transform", transform);

					}

					if (sceneEntity->HasComponent(ComponentType::LightComponent)) {


						Component* comp = sceneEntity->GetComponent(ComponentType::LightComponent);

						LightComponent* lightComp = dynamic_cast<LightComponent*>(comp);
						Light* sceneLight;

						if (lightComp) {

							sceneLight = lightComp->GetLight();
						}



						switch (lightComp->GetLightType()) {

						case LightType::Directional: {

							toml::table light;

							light.insert("type", "directional");


							DirectionalLight* directionalLight = dynamic_cast<DirectionalLight*>(sceneLight);

							toml::table properties;

							if (directionalLight) {

								DirectionalLightProps& dirLightProps = directionalLight->GetLightProperties();

								properties.insert("color", toml::array(dirLightProps.color.r, dirLightProps.color.g, dirLightProps.color.b));
								properties.insert("intensity", dirLightProps.intensity);

								light.insert("properties", properties);
							}


							entity.insert("light", light);




							break;
						}

						case LightType::Point: {

							toml::table light;
							light.insert("type", "point");

							Light* sceneLight = lightComp->GetLight();
							PointLight* pointLight = dynamic_cast<PointLight*>(sceneLight);

							toml::table properties;

							if (pointLight) {

								PointLightProps& pointLightProps = pointLight->GetLightProperties();

								properties.insert("color", toml::array(pointLightProps.color.r, pointLightProps.color.g, pointLightProps.color.b));
								properties.insert("intensity", pointLightProps.intensity);
								properties.insert("position", toml::array(pointLightProps.position.x, pointLightProps.position.y, pointLightProps.position.z));

								light.insert("properties", properties);
							}

							entity.insert("light", light);


							break;
						}

						case LightType::Spot: {

							toml::table light;
							light.insert("type", "spot");

							Light* sceneLight = lightComp->GetLight();
							SpotLight* spotLight = dynamic_cast<SpotLight*>(sceneLight);

							toml::table properties;

							if (spotLight) {

								SpotLightProps& spotLightProps = spotLight->GetLightProperties();

								properties.insert("color", toml::array(spotLightProps.color.r, spotLightProps.color.g, spotLightProps.color.b));
								properties.insert("intensity", spotLightProps.intensity);
								properties.insert("position", toml::array(spotLightProps.position.x, spotLightProps.position.y, spotLightProps.position.z));
								properties.insert("direction", toml::array(spotLightProps.direction.x, spotLightProps.direction.y, spotLightProps.direction.z));
								properties.insert("spread", spotLightProps.spread);

								light.insert("properties", properties);
							}

							entity.insert("light", light);


							break;
						}

						case LightType::SkyLight: {

							break;

						}

						}
					}





					break;
				}


				case EntityType::Camera: {

					entity.insert("type", "camera");


					break;
				}

				}



				data.insert(it->get()->GetEntityName(), entity);

				//Setting required states
				mScene->setSceneSerializeState(SerializeState::Serialized);
				mScene->setSerializedPath(filepath);


			}
			catch (const toml::parse_error& e) {

				std::cerr << "Error (Serialize): " << e.what() << std::endl;
			}

			catch (const std::exception& e) {
				std::cerr << "Error (Serialize): " << e.what() << std::endl;
			}



		}


		std::stringstream toml_stream;

		toml_stream << data;

		std::ofstream ofs(filepath.string());

		ofs << toml_stream.str();

		ofs.close();



	}




	void SceneSerializer::Deserialize(const std::filesystem::path& filepath) {

		//Clearing the scene before deserializing
		mScene->ClearScene();

		try {

			auto data = toml::parse_file(filepath.string());

			if (data.is_table()) {

				for (const auto& [key, value] : data) {

					std::string key_str = (std::string)key.str();

					if (value.is_table()) {

						toml::table& sub_table = *value.as_table();

						if (sub_table.contains("type")) {

							std::optional name_value = sub_table["name"].value<std::string>();
							std::optional type_value = sub_table["type"].value<std::string>();
							std::optional id_value = sub_table["id"].value<int>();

							if (name_value.has_value() && type_value.has_value() && id_value.has_value()) {

								if (type_value.value() == "model") {

									std::optional model_path_value = sub_table["model_path"].value<std::string>();

									if (model_path_value.has_value()) {

										Scene::nextEntityID++;

										std::filesystem::path model_path = std::filesystem::path(model_path_value.value());

										Ref<Entity> modelEntity = CreateRef<Model>(name_value.value(), id_value.value(), EntityType::Model, model_path);


										if (std::dynamic_pointer_cast<Model>(modelEntity)->IsReadSuccessful()) {

											if (modelEntity->HasComponent(ComponentType::TransformComponent)) {

												TransformComponent* transComp = dynamic_cast<TransformComponent*>(modelEntity->GetComponent(ComponentType::TransformComponent));

												if (transComp) {

													if (sub_table.contains("transform")) {

														toml::table& transform_table = *sub_table["transform"].as_table();

														const toml::array* position = transform_table["position"].as_array();
														const toml::array* scale = transform_table["scale"].as_array();

														if (position && scale) {

															transComp->SetPosition({

																position->get(0)->value_or(0.0),
																position->get(1)->value_or(0.0),
																position->get(2)->value_or(0.0)

																});

															transComp->SetScale({

																scale->get(0)->value_or(0.0),
																scale->get(1)->value_or(0.0),
																scale->get(2)->value_or(0.0)

																});

															transComp->OnUpdate();


														}

													}

												}

											}

											if (sub_table.contains("material")) {

												toml::table& material_table = *sub_table["material"].as_table();

												if (material_table.contains("type")) {

													std::optional material_type_value = material_table["type"].value<std::string>();

													if (material_type_value.has_value()) {

														if (material_type_value.value() == "pbr") {

															if (material_table.contains("textures")) {

																toml::table& textures_table = *material_table["textures"].as_table();

																std::optional albedo_path_value = textures_table["albedo"].value<std::string>();
																std::optional normal_path_value = textures_table["normal"].value<std::string>();

																if (albedo_path_value.has_value() && normal_path_value.has_value()) {


																	modelEntity->AddComponent(new MaterialComponent(CreateRef<PBR_Material>()));

																	if (modelEntity->HasComponent(ComponentType::MaterialComponent)) {

																		MaterialComponent* comp = dynamic_cast<MaterialComponent*>(modelEntity->GetComponent(ComponentType::MaterialComponent));
																		Ref<PBR_Material> mat = std::dynamic_pointer_cast<PBR_Material>(comp->GetMaterial());

																		if (albedo_path_value.value() != "none") {


																			//Create the texture from the given path
																			Ref<Texture2D> texMap = Texture2D::Create(albedo_path_value.value());

																			//Update the texture set
																			mat->Update(texMap, MapType::Albedo, std::filesystem::path(albedo_path_value.value()));


																		}

																		if (normal_path_value.value() != "none") {

																			//Create the texture from the given path
																			Ref<Texture2D> texMap = Texture2D::Create(normal_path_value.value());

																			mat->Update(texMap, MapType::Normal, std::filesystem::path(normal_path_value.value()));

																		}
																	}

																	
																	

																}

															}


														}

														if (material_type_value.value() == "basic") {

															if (material_table.contains("properties")) {

																toml::table& material_properties_table = *material_table["properties"].as_table();

																const toml::array* color = material_properties_table["color"].as_array();

																if (color) {

																	modelEntity->AddComponent(new MaterialComponent(CreateRef<BASIC_Material>()));

																	if (modelEntity->HasComponent(ComponentType::MaterialComponent)) {

																		MaterialComponent* comp = dynamic_cast<MaterialComponent*>(modelEntity->GetComponent(ComponentType::MaterialComponent));
																		Ref<BASIC_Material> mat = std::dynamic_pointer_cast<BASIC_Material>(comp->GetMaterial());

																		//Updating material properties
																		mat->SetColor({
																			
																			color->get(0)->value_or(1.0),
																			color->get(1)->value_or(1.0),
																			color->get(2)->value_or(1.0),
																			color->get(3)->value_or(1.0)

																			});

																	}

																}
															}



														}

													}

												}


											}


											mScene->AddEntity(modelEntity);


										}

									}

								}

							}


						}

					}

				}

			}



			mScene->setSceneSerializeState(SerializeState::Serialized);
			mScene->setSerializedPath(filepath);


		}

		catch (toml::parse_error& e) {

			std::cerr << "Error (Deserialize) : " << e.what() << std::endl;

		}

		catch (const std::exception& e) {

			std::cout << "Error (Deserialize): " << e.what() << std::endl;

		}



	}

}
#pragma once

#include <string>

#include <Rayer/Component/Component.h>

namespace Rayer {

	enum class EntityType {

		Model,
		Camera,
		Light,

	};
	
	class Entity {

	public:

		template <typename T>
		using iterator = std::vector<T>::iterator;
		template <typename T>
		using const_iterator = std::vector<T>::const_iterator;

		Entity() = default;
		Entity(const std::string& _name, int _id , EntityType _type) : name(_name), type(_type) , id(_id) {}

		virtual ~Entity() {
		
			for (auto& component : components) {
				delete component;
			}

			components.clear();

		};

		EntityType GetEntityType() const { return type; }
		std::string GetEntityName() const { return name; }

		int GetEntityID() { return id; }


		void AddComponent(Component* _component) {

			components.push_back(std::move(_component));

		}

		void RemoveComponent(Component* _component) {

			components.erase(std::remove(components.begin(), components.end(), _component), components.end());
		}

		bool HasComponent(ComponentType _type) {

			for (auto& component : components) {
				
				if (component->GetComponentType() == _type) {
					return true;
				}
			}

			return false;

		}

		Component* GetComponent(ComponentType _type) {

			if (HasComponent(_type)) {

				for (auto& component : components) {

					if (component->GetComponentType() == _type) {
						return component;
					}

				}

			}

			else {

				#ifdef RAYER_DEBUG
					std::cout << "Component not found!" << std::endl;
				#endif

				return nullptr;
			}

		}

		//Getting components iterators

		//[NON CONST]
		iterator<Component*> beginComponentIterator() { return components.begin(); }
		iterator<Component*> endComponentIterator() { return components.end(); }

		//[CONST]
		const_iterator<Component*> beginComponentIteratorC() const { return components.begin(); }
		const_iterator<Component*> endComponentIteratorC() const { return components.end(); }


	private:

		std::string name;
		EntityType type;

		int id;

		std::vector <Component*> components{};
	};

}